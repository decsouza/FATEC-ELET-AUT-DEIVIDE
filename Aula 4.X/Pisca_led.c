/*******************************************************************************
 FileName:     Pisca_Led - FATEC SANTO ANDR�
 Dependencies: Veja a se��o de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         03/09/2020
 Software License Agreement: Somente para fins did�ticos
 *******************************************************************************
 File Description: Este programa gera um pisca pisca numa sa�da determinada.
 Change History:
 1.0   03/09/2020  Vers�o inicial
 
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

#define RB7 PORTBbits.RB7


/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: 
/******************************************************************************/

void main()
{
    ADCON1 = 0X0F; // Define somente as entradas digitais
    TRISB = 0X00; // Define todos os pinos B como sa�das 
    LATB = 0XFF;
    
    while(1){
        RB7 = 1;
        delay_ms(500);
        RB7 = 0;
        delay_ms(500);
    }         
    
}

/******************************************************************************               
* Funcao:   delay_ms(unsigned int delaytime)
* Entrada:  unsigned int delaytime - recebe valores de 0 a 65536
* Saida:    Nenhuma (void)
* Descricao: Gera um atraso de tempo conforme o valor recebido de delaytime
             O tempo interno � baseado no delay 1 ms. Assim, a cada loop temos o
 *           decremento da vari�vel delaytime, at� que ele atinja zero. Exemplo:
 *           se o delyatime = 500 a fun��o terminar� e retornar� para o programa
 *           principal ap�s 500 ms.
/******************************************************************************/

void delay_ms(unsigned int tempodeatraso)
{
    while(--tempodeatraso){
        __delay_ms(1); //Gera um atraso de 1ms
    }
}