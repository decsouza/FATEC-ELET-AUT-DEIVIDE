/*******************************************************************************
 FileName:     Aula 7 - interrupção Externa - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         05/11/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa testa a utilização de interrupção INT0, utilizando 
 * um botão
 1.0   5/11/2020  Versão inicial
 
*******************************************************************************/


// Includes do Compilador

#include<p18f4550.h>
//#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

// Protótipos das Funções 

void delay_ms(unsigned int tempodeatraso);
void interrupt high_priority InterrupcoesAlta(void); // Alta Prioridade


/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: Verifica o overflow do timer 0 a cada 10 pulsos do sinal externo 
 * proveniente do botão B1 e, a cada overflow, acende em sequencia os leds nas 
 * portas RB.
/******************************************************************************/

unsigned char contador;
unsigned char contadorB;

void main(void) {
       
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="  INTERRUPCOES  ";
    const unsigned char Texto_2[]="CONTADOR =      ";
    const unsigned char Texto_3[]="                ";
    
    ADCON1 = 0X0F; //Define somente as portas digitais;
    TRISB = 0X03; // pinos 0 e 1 como entradas
    PORTB = 0X0F;
              
    //Habilita interrupção externa 0 e 1
    // Pino B0 e B1 são entradas e pinos B[2-7] são saídas
    
    INTCONbits.RBIE = 0;
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCONbits.GIE = 1;
        

    
    ConfiguraLCD(); // prepara o display LCD 
    DesligaCursor();
    EscreveFraseRamLCD(Texto_0); 
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(3000); // pausa para mostrar as boas vindas
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_2);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_2);
    
    
    while(1){
        delay_ms(5000); // pausa 
        PosicaoCursorLCD(1, 12);
        EscreveInteiroLCD(contador);       
        PosicaoCursorLCD(2, 12);
        EscreveInteiroLCD(contadorB);  
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
        INT0IF = 0;// Libera Interrupçao
    }
    if(INT1IE && INT1IF){        
        PORTBbits.RB6 = !PORTBbits.RB6;
        contadorB++;
        INT1IF = 0;// Libera Interrupçao
    }
    
}