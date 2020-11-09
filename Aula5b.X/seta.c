/*******************************************************************************
 FileName:     Seta - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         03/09/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa simula o funcionamento dos indicadores de 
 * direção acionados por botões.
 Change History:
 1.0   18/09/2020  Versão inicial
 1.1   29/09/2020  Inclusão do uso do terceiro botão com a funcionalidade da 
 * luz de advertência
 * 
 
*******************************************************************************/

// Includes do Compilador

#include<p18f4550.h>
#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"

// Protótipos das Funções 

void delay_ms(unsigned int temodeatraso);

// Define os apelidos das variáveis do PIC

#define setas PORTB

#define botaoEsq PORTEbits.RE0
#define botaoDir PORTEbits.RE1
#define botaoPiscaPisca PORTEbits.RE2 // botão advertência

/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: 
/******************************************************************************/

void main(void) 
{
    ADCON1 = 0X0F; //Define somente as portas digitais;
    TRISB = 0X00; //Define todos os pinos como saída
    TRISE = 0b11111111; //Define todos os pinos como entrada
    PORTB = 0XFF; //Definindo todos os leds como apagados ao iniciar
    char cont; //variável para o contador
    unsigned int atraso = 200; //variável de atraso
        
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
            if(botaoPiscaPisca == 0) // botão advertência
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