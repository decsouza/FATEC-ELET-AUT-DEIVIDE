/*******************************************************************************
 FileName:     Seta - FATEC SANTO ANDR�
 Dependencies: Veja a se��o de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         03/09/2020
 Software License Agreement: Somente para fins did�ticos
 *******************************************************************************
 File Description: Este programa simula o funcionamento dos indicadores de 
 * dire��o acionados por bot�es.
 Change History:
 1.0   18/09/2020  Vers�o inicial
 1.1   29/09/2020  Inclus�o do uso do terceiro bot�o com a funcionalidade da 
 * luz de advert�ncia
 * 
 
*******************************************************************************/

// Includes do Compilador

#include<p18f4550.h>
#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"

// Prot�tipos das Fun��es 

void delay_ms(unsigned int temodeatraso);

// Define os apelidos das vari�veis do PIC

#define setas PORTB

#define botaoEsq PORTEbits.RE0
#define botaoDir PORTEbits.RE1
#define botaoPiscaPisca PORTEbits.RE2 // bot�o advert�ncia

/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: 
/******************************************************************************/

void main(void) 
{
    ADCON1 = 0X0F; //Define somente as portas digitais;
    TRISB = 0X00; //Define todos os pinos como sa�da
    TRISE = 0b11111111; //Define todos os pinos como entrada
    PORTB = 0XFF; //Definindo todos os leds como apagados ao iniciar
    char cont; //vari�vel para o contador
    unsigned int atraso = 200; //vari�vel de atraso
        
    while(1)
    {
        if(botaoEsq == 0)
        {
            setas = 0b11101111;
            for(cont = 0; cont<=3; cont++){
               delay_ms(atraso);
               setas = setas << 1 | 0b00001111; 
            }
        }
        if(botaoDir == 0)
        {
            setas = 0b11110111;
            for(cont = 0; cont<=3; cont++){
               delay_ms(atraso);
               setas = setas >> 1 | 0b11110000; 
            }           
        }   
            if(botaoPiscaPisca == 0) // bot�o advert�ncia
        {
            setas = 0b00000000;
            delay_ms(500);  
            setas = 0b11111111;
            delay_ms(500);  
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