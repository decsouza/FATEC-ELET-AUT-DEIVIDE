/*******************************************************************************
 FileName:     Aula 7 - interrup��o Externa - FATEC SANTO ANDR�
 Dependencies: Veja a se��o de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         05/11/2020
 Software License Agreement: Somente para fins did�ticos
 *******************************************************************************
 File Description: Este programa testa a utiliza��o de interrup��o INT0, utilizando 
 * um bot�o
 1.0   5/11/2020  Vers�o inicial
 
*******************************************************************************/


// Includes do Compilador

#include<p18f4550.h>
#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

// Prot�tipos das Fun��es 

void delay_ms(unsigned int tempodeatraso);
void interrupt high_priority InterrupcoesAlta(void); // Alta Prioridade


/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: Verifica o overflow do timer 0 a cada 10 pulsos do sinal externo 
 * proveniente do bot�o B1 e, a cada overflow, acende em sequencia os leds nas 
 * portas RB.
/******************************************************************************/

unsigned char contador = 0;

void main(void) {
       
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="  INTERRUPCOES  ";
    const unsigned char Texto_2[]="CONTADOR =      ";
    const unsigned char Texto_3[]="                ";
    
    ADCON1 = 0XFF; //Define somente as portas digitais;
    TRISB = 0X03; // pinos 0 e 1 como entradas
    TRISE = 0XFF; // todos os pinos como entradas
    LATB = 0XFF; // escreve na mem�ria LATB 1 nos 8 bits
              
    //Habilita interrup��o externa 0 e 1
    // Pino B0 e B1 s�o entradas e pinos B[2-7] s�o sa�das
    
    INTCONbits.RBIE = 0; 
    INTCONbits.INT0IE = 1; //Habilita a interrup��o INT0
    INTCON3bits.INT1IE = 1; //Habilita a interrup��o INT1
    
    INTCONbits.GIE = 1; 
    INTCONbits.GIEH = 1;
    
    IPEN = 0; // todas as interrup��es
    INTCON2bits.INTEDG0 = 0; // bora de descida intcon0
    
    ConfiguraLCD(); // prepara o display LCD 
    DesligaCursor();
    EscreveFraseRamLCD(Texto_0); 
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(3000); // pausa para mostrar as boas vindas
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_2);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    
    
    while(1){
        PosicaoCursorLCD(1, 12);
        EscreveInteiroLCD(contador);       
        if(PORTEbits.RE2 == 0){
            contador = 0;     
            PosicaoCursorLCD(1,12);
            EscreveFraseRamLCD("0  ");
            
        }
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

    if(INT0IE && INT0IF){        
        PORTBbits.RB7 = !PORTBbits.RB7;
        contador++;
        INT0IF = 0;// Libera Interrup�ao
    }
    if(INT1IE && INT1IF){        
        PORTBbits.RB6 = !PORTBbits.RB6;
        if(contador > 0){
            contador--;
        }
        INT1IF = 0;// Libera Interrup�ao
    }

    
}