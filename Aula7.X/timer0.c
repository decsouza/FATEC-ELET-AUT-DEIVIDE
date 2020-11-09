/*******************************************************************************
 FileName:     Timer 0 - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         21/10/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa liga o led rb7 a cada 30 segundos, utilizando o
 * clock interno de 12Mhz
 1.0   22/10/2020  Versão inicial
 
*******************************************************************************/


// Includes do Compilador

#include<p18f4550.h>
//#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

// Protótipos das Funções 

void delay_ms(unsigned int temodeatraso);

void main(void) {
    //utilizando o T0CON
    T0CON = 0b10000111;
    //TMR0ON = 1; // liga o módulo do timer0 - bit7
    //T08BIT = 0; // seleciona o modo 16 bits - bit6
    //T0CS = 0; // seleciona clock interno - bit5
    //PSA = 0; // seleciona sinal do prescaler - bit3
    //T0PS2 = 1; // seleciona prescaler 256 - bit2
    //T0PS1 = 1; - bit1
    //T0PS0 = 1; - bit0

    
    TMR0L = 0xe5; // recarrega o inicio do timer0 - 18661
    TMR0H = 0x48; // recarrega o inicio do timer0 - 18661
    
    ADCON1 = 0x0f;
    TRISB = 0x00; // portas como saída
    PORTB = 0b11111111; // deixando os leds apagados
    
    unsigned char contador; // variável para contagem
    
    ConfiguraLCD();  
    PosicaoCursorLCD(1,1);
    EscreveFraseLCD("CONTADOR ");
    
    while(1)
    {
        if(TMR0IF == 1)
        {
            TMR0IF = 0;
            contador++;
            TMR0L = 0xe5; 
            TMR0H = 0x48;            
            if(contador >= 30)
            {
                PORTBbits.RB7 = !PORTBbits.RB7;
                contador = 0;
              }
            PosicaoCursorLCD(1,10);
            EscreveInteiroLCD(contador);
        }
    }
    
}
