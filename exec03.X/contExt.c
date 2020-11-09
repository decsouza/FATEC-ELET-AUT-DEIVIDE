/*******************************************************************************
 FileName:     Exerc�cio 3 - Simulador de Contador Externo - FATEC SANTO ANDR�
 Dependencies: Veja a se��o de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         31/10/2020
 Software License Agreement: Somente para fins did�ticos
 *******************************************************************************
 File Description: Este programa simula um sinal de pulso externo (clock) e a cada
 * 10 pulsos de clock liga os leds nas portas RB.
 1.0   31/10/2020  Vers�o inicial
 
*******************************************************************************/



//Ligar um Jumper nas portas RA4 e RE0


// Includes do Compilador

#include<p18f4550.h>
//#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

// Prot�tipos das Fun��es 

void delay_ms(unsigned int temodeatraso);


/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: Verifica o overflow do timer 0 a cada 10 pulsos do sinal externo 
 * proveniente do bot�o B1 e, a cada overflow, acende em sequencia os leds nas 
 * portas RB.
/******************************************************************************/

void main(void) {
    
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="CLOCK EXTERNO T0";
    const unsigned char Texto_2[]="PRESS. 10X BTNB1";
    const unsigned char Texto_3[]="                ";
        

    T0CON = 0b11101000;     //utilizando o T0CON - ao inv�s de cada instru��o abaixo
    //TMR0ON = 1; // liga o m�dulo do timer0 - bit7
    //T08BIT = 1; // seleciona o modo 8 bits - bit6
    //T0CS = 1; // seleciona clock externo - bit5
    
    //PSA = 1; // prescaler n�o selcionado - bit3
    //T0PS2 = 0; // n�o usado - bit 2
    //T0PS1 = 0; n�o usado - bit1
    //T0PS0 = 0; n�o usado - bit0
    
    TMR0L = 0xF6; // recarrega o inicio do timer0     
    ADCON1 = 0X0F; //Define somente as portas digitais;
    TRISB = 0X00; // portas como sa�da    
    PORTB = 0b11111111; // inicia com os leds apagados
        
       
    ConfiguraLCD(); // prepara o display LCD 
    DesligaCursor();
    EscreveFraseRamLCD(Texto_0); 
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(5000); // pausa para mostrar as boas vindas
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_1);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_2);
    
    while(1)
    {   
        if(TMR0IF == 1)
        {            
            if(PORTB == 0b00000000) // verifica se todos os leds est�o acesos, se verdadeiro apaga os leds para iniciar novamente o processo
            {
                PORTB = 0b11111111; // apaga todos os leds 
            }
            else // processo de acender os leds >>
            {
                PORTB = PORTB >> 1; // desloca 1 bit para a direita - acendendo o pr�ximo led
            }
            TMR0IF = 0; // zera o indicador de overflow do contador
            TMR0L = 0xF6; // pr� carga do contador - 246
        }     
    }
}


/******************************************************************************               
* Funcao:   delay_ms(unsigned int delaytime)
* Entrada:  unsigned int delaytime - recebe valores de 0 a 65536
* Saida:    Nenhuma (void)
* Descricao: Gera um atraso de tempo conforme o valor recebido de delaytime
             O tempo interno � baseado no delay 1 ms. Assim, a cada loop temos o
 *           decremento da vari�vel delaytime, at� que ele atinja zero. Exemplo:
 *           se o delaytime = 500 a fun��o terminar� e retornar� para o programa
 *           principal ap�s 500 ms.
/******************************************************************************/


void delay_ms(unsigned int tempodeatraso)
{
    while(--tempodeatraso){
        __delay_ms(1); //Gera um atraso de 1ms
    }
}