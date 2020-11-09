/*******************************************************************************
 FileName:     Exercício 2 - radar automotivo - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         25/10/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa utiliza o timer 0 para a contagem de tempo e os 
 * botões b1 e b2 para simular os sensores no asfalto, e assim calcular a veloci-
 * dade do veículo
 1.0   25/10/2020  Versão inicial
 
*******************************************************************************/


// Includes do Compilador

#include<p18f4550.h>
//#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto


//definindo os apelidos

#define botaoB1 PORTEbits.RE0 
#define botaoB2 PORTEbits.RE1 

#include "Config.h"
#include "displayLCD.h"

// Protótipos das Funções 

void delay_ms(unsigned int temodeatraso);

void main(void) {
    
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="RADAR VELOCIDADE";
    const unsigned char Texto_3[]="          km h  ";
    const unsigned char Texto_4[]="                ";

        
    //utilizando o T0CON
    T0CON = 0b10001000;
    //TMR0ON = 1; // liga o módulo do timer0 - bit7
    //T08BIT = 0; // seleciona o modo 16 bits - bit6
    //T0CS = 0; // seleciona clock interno - bit5
    //PSA = 1; // prescaler não selcionado - bit3
    //T0PS2 = 0; // não usado - bit 2
    //T0PS1 = 0; não usado - bit1
    //T0PS0 = 0; não usado - bit0

    
    TMR0L = 0x20; // recarrega o inicio do timer0 
    TMR0H = 0xD1; // recarrega o inicio do timer0 
    
    ADCON1 = 0X0F; //Define somente as portas digitais;
    TRISE = 0xFF; // portas como entrada
    
    
    unsigned int contador; // variável para contagem
    unsigned int velocidade;
    unsigned int velocInt;
    unsigned int velocDec;
    
    
    ConfiguraLCD(); // prepara o display LCD 
    DesligaCursor();
    EscreveFraseRamLCD(Texto_0);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(5000);
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_1);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_4);
    
    while(1)
    {
        if(botaoB1 == 0)
        {
            contador = 0;
            while(botaoB2 != 0)
            {
                if(TMR0IF == 1){
                     TMR0IF = 0;
                     contador++;
                     TMR0L = 0x20; 
                     TMR0H = 0xD1; 
                }                
            }
            if(contador != 0){
                velocidade = 36000 / contador;
                velocInt = velocidade / 10;
                velocDec = velocidade - velocInt;
                
                PosicaoCursorLCD(2,1);
                EscreveFraseRamLCD(Texto_3);
                PosicaoCursorLCD(2,3);
                EscreveInteiroLCD(velocInt);
                PosicaoCursorLCD(2,6);
                EscreveFraseRamLCD(".");
                PosicaoCursorLCD(2,7);
                EscreveInteiroLCD(velocDec); 
            }
        }

    }
         
}

void delay_ms(unsigned int tempodeatraso)
{
    while(--tempodeatraso){
        __delay_ms(1); //Gera um atraso de 1ms
    }
}