/*******************************************************************************
 FileName:     Seta - FATEC SANTO ANDR�
 Dependencies: Veja a se��o de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         24/09/2020
 Software License Agreement: Somente para fins did�ticos
 *******************************************************************************
 File Description: Este programa simula o funcionamento dos indicadores de 
 * dire��o acionados por bot�es. e implementada a fun��o LCD
 Change History:
 1.0   24/09/2020  Vers�o inicial
 1.1   25/09/2020  Implanta��o da fun��o frenagem 
 * 
 
*******************************************************************************/

// Includes do Compilador

#include<p18f4550.h>
#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

// Prot�tipos das Fun��es 

void delay_ms(unsigned int temodeatraso);

// Define os apelidos das vari�veis do PIC

#define setas PORTB

#define botaoEsq PORTEbits.RE0
#define botaoDir PORTEbits.RE1
#define botaoB3 PORTEbits.RE2 // bot�o frenagem

/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: 
/******************************************************************************/

void main(void) 
{
    ADCON1 = 0x0F; //Define somente as portas digitais;
    TRISB = 0x00; //Define todos os pinos como sa�da
    TRISE = 0b11111111; //Define todos os pinos como entrada
    PORTB = 0xFF; //Definindo todos os leds como apagados ao iniciar
    char cont; //vari�vel para o contador
    unsigned int atraso = 125; //vari�vel de atraso
    
    //Defini��o das vari�veis do programa
    
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="SETA SEQUENCIAL ";
    const unsigned char Texto_2[]="SETA P/ ESQUERDA";
    const unsigned char Texto_3[]="SETA P/ DIREITA ";
    const unsigned char Texto_4[]="    FRENANDO    ";
    const unsigned char Texto_5[]="                ";
    
    //Configura e prepara o Display LCD
    
    ConfiguraLCD(); // prepara o display LCD 
    
    EscreveFraseRamLCD(Texto_0);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(5000);
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_1);
    
        
    while(1)
    {
        if(botaoEsq == 0)
        {
            setas = 0b11101111;
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD(Texto_2);
            for(cont = 0; cont<=3; cont++){
               delay_ms(atraso);
               setas = setas << 1 | 0b00001111; 
            }
        }
        if(botaoDir == 0)
        {
            setas = 0b11110111;
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD(Texto_3);
            for(cont = 0; cont<=3; cont++){
               delay_ms(atraso);
               setas = setas >> 1 | 0b11110000; 
            }           
        }   
        if(botaoB3 == 0) // bot�o frenagem
        {
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD(Texto_4);
            setas = 0b00000000;
            delay_ms(500);  
        }
        else
        {
        setas = 0b11111111; 
        PosicaoCursorLCD(2,1);
        EscreveFraseRamLCD(Texto_5);  
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