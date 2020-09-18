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

#define setaEsqD PORTBbits.RB7
#define setaEsqC PORTBbits.RB6
#define setaEsqB PORTBbits.RB5
#define setaEsqA PORTBbits.RB4
#define setaDirA PORTBbits.RB3
#define setaDirB PORTBbits.RB2
#define setaDirC PORTBbits.RB1
#define setaDirD PORTBbits.RB0

#define botaoEsq PORTEbits.RE0
#define botaoDir PORTEbits.RE1

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
    
        
    while(1)
    {
        if(botaoEsq == 0)
        {
            setaEsqA = 0;
            delay_ms(100);
            setaEsqB = 0;
            delay_ms(100);
            setaEsqC = 0;
            delay_ms(100);
            setaEsqD = 0;
            delay_ms(100);
            setaEsqA = 1;
            setaEsqB = 1;
            setaEsqC = 1;
            setaEsqD = 1;    
            delay_ms(100);
        }
        if(botaoDir == 0)
        {
            setaDirA = 0;
            delay_ms(100);
            setaDirB = 0;
            delay_ms(100);
            setaDirC = 0;
            delay_ms(100);
            setaDirD = 0;
            delay_ms(100);
            setaDirA = 1;
            setaDirB = 1;
            setaDirC = 1;
            setaDirD = 1;
            delay_ms(100);            
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