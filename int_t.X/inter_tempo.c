/*******************************************************************************
 FileName:     Aula 7 - interrupção Timer0 - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         05/11/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa utiliza a interrupção INT0, UNT1 e TIMER0, 
 * utilizando botões
 1.0   5/11/2020  Versão inicial
 
*******************************************************************************/


// Includes do Compilador

#include<p18f4550.h>
#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

// Protótipos das Funções 

void delay_ms(unsigned int tempodeatraso);
void interrupt high_priority InterrupcoesAlta(void); // Alta Prioridade


//variáveis globais

unsigned char contador = 0;
unsigned int tempo = 0;
unsigned int vezes = 1;
unsigned int tempoAcionado = 0;


/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: Verifica o overflow do timer 0 a cada 10 pulsos do sinal externo 
 * proveniente do botão B1 e, a cada overflow, acende em sequencia os leds nas 
 * portas RB.
/******************************************************************************/



void main(void) {
       
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="  INTERRUPCOES  ";
    const unsigned char Texto_2[]="TEMPO =         ";
    const unsigned char Texto_3[]="FREQ. BT0 =     ";
    const unsigned char Texto_4[]="                ";
    
    ADCON1 = 0XFF; //Define somente as portas digitais;
    TRISB = 0X03; // pinos 0 e 1 como entradas
    TRISE = 0XFF; // todos os pinos como entradas
    LATB = 0XFF; // escreve na memória LATB 1 nos 8 bits
              

    
    //configura o timer0  como interrupção
    
    TMR0IE = 1;
    
    
    //configura o timer
    
    T0CON = 0b11000011;     //utilizando o T0CON - ao invés de cada instrução abaixo
    //TMR0ON = 1; // liga o módulo do timer0 - bit7
    //T08BIT = 1; // seleciona o modo 8 bits - bit6
    //T0CS = 0; // seleciona clock interno - bit5
    
    //PSA = 0; // prescaler selcionado - bit3
    //T0PS2 = 0; //  - bit 2
    //T0PS1 = 1; // - bit1
    //T0PS0 = 0; // - bit0
        
    //Habilita interrupção externa 0 e 1
    // Pino B0 e B1 são entradas e pinos B[2-7] são saídas
    
    INTCONbits.RBIE = 0; 
    INTCONbits.INT0IE = 1; //Habilita a interrupção INT0
    INTCON3bits.INT1IE = 1; //Habilita a interrupção INT1
    
    INTCONbits.GIE = 1; 
    INTCONbits.GIEH = 1;
    
    INTEDG0 = 0; // seleciona  a interrupção na borda de descida
    
    
    IPEN = 0; // todas as interrupções
    INTCON2bits.INTEDG0 = 0; // bora de descida intcon0
    
    
    //variáveis locais
    unsigned char segundos;
    unsigned int milisegundos;
    unsigned int freq = 0;
    
    ConfiguraLCD(); // prepara o display LCD 
    DesligaCursor();
    EscreveFraseRamLCD(Texto_0); 
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(3000); // pausa para mostrar as boas vindas
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_2);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_3);
    
    
    
    while(1){
        freq = 1 / tempoAcionado;
        PosicaoCursorLCD(1, 9);
        EscreveInteiroLCD(tempoAcionado/100);      
        //PosicaoCursorLCD(1, 11);
        //EscreveFraseRamLCD(",");
        //PosicaoCursorLCD(1,12);
        //EscreveInteiroLCD(0);      
        PosicaoCursorLCD(2,13);
        EscreveInteiroLCD(tempo*vezes /100);     
        PosicaoCursorLCD(2,15);
        EscreveFraseRamLCD("Hz");        
    }
    
    
    
    return;
}

void delay_ms(unsigned int tempodeatraso)
{
    while(--tempodeatraso){
        __delay_ms(1); //Gera um atraso de 1ms
    }
}

void interrupt high_priority InterrupcoesAlta(void) // Alta Prioridade
{    
    if(TMR0IF == 1)
    {
        INTCONbits.TMR0IF = 0;
        tempo++;
        TMR0L = 106 + TMR0L;        
        if(tempo > 29999)
        {
            vezes++;
            tempo = 0;
        }
    }

    if(INT0IE && INT0IF INTEDG0 = 1)
    {    
        INT0IF = 0;// Libera Interrupçao
        PORTBbits.RB7 = !PORTBbits.RB7;
        contador++;
        tempoAcionado = tempo*vezes;
    }
    
        if(INT0IE && INT0IF && INTEDG0 = 0)
    {    
        INT0IF = 0;// Libera Interrupçao
        PORTBbits.RB7 = !PORTBbits.RB7;
        tempoAcionado = (tempo*vezes) - tempoAcionado;
    }
    
    if(INT1IE && INT1IF){        
        PORTBbits.RB6 = !PORTBbits.RB6;
        if(contador > 0){
            contador--;
        }
        INT1IF = 0;// Libera Interrupçao
    }

    
}