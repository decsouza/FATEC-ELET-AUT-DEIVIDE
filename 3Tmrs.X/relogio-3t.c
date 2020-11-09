/*******************************************************************************
 FileName:     Exercício - 3 Timers Externos - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         02/11/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa testa a utilização dos timers, 0, 1 e 3, 
 * para criar um relógio
 1.0   31/10/2020  Versão inicial
 
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
void pos_numero(unsigned char valor, unsigned char casa);


/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: Verifica o overflow do timer 0 a cada 10 pulsos do sinal externo 
 * proveniente do botão B1 e, a cada overflow, acende em sequencia os leds nas 
 * portas RB.
/******************************************************************************/

void main(void) {
    
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="RELOGIO 3 TIMERS";
    const unsigned char Texto_2[]="--- 00:00:00 ---";
    const unsigned char Texto_3[]="                ";
        

    T0CON = 0b10000011;     //utilizando o T0CON - ao invés de cada instrução abaixo
    //TMR0ON = 1; // liga o módulo do timer0 - bit7
    //T08BIT = 0; // seleciona o modo 16 bits - bit6
    //T0CS = 0; // seleciona clock interno - bit5
    
    //PSA = 0; // prescaler selcionado - bit3
    //T0PS2 = 0; //  - bit 2
    //T0PS1 = 1; // - bit1
    //T0PS0 = 1; // - bit0
            
    TMR0 = 0x6D84; //pré-carga 28036
    //TMR0L = 0x84; // recarrega o inicio do timer0   28036  
    //TMR0H = 0x6D; // recarrega o inicio do timer0   28036  
    
    
    T1CON = 0b10000111;     //T1CON 
    //RD16 = 1; // operação 1 16-bit 
    //T1RUN = 0; // flag 
    //T1CKPS1 = 0; // prescaler 1
    //T1CKPS1 = 0; // prescaler 1
    //T1OSCEN = 0; // Oscilador desabilitado
    //T1SYNC = 1 // assíncrono
    //TMR1CS = 1; // seleciona Clock externo
    //TMR1ON = 1; // liga o timer
            
              
    TMR1 = 0xFFF6; // pré-carga 65516
    //TMR1L = 0xFB; // recarrega o inicio do timer1   28036  
    //TMR1H = 0xFF; // recarrega o inicio do timer1   28036  
    
    
    T3CON = 0b00000111;     //T3CON 
    TMR3 = 0xFDA8; // recarrega o inicio do timer3   28036  
    
    
    ADCON1 = 0X0F; //Define somente as portas digitais;
    
    TRISB = 0X00; // portas como saída 
    PORTB = 0b11111111; // inicia com os leds apagados
    
    unsigned int milisegundos = 0;
    unsigned char segundos = 0;
    unsigned char minutos = 0;
    unsigned char horas = 0;
    unsigned int contador;
    
        
    ConfiguraLCD(); // prepara o display LCD 
    DesligaCursor();
    EscreveFraseRamLCD(Texto_0); 
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(2000); // pausa para mostrar as boas vindas
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_1);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_2);
    


    while(1)
    {   
        
        if(TMR0IF == 1)
        {                        
            PORTBbits.RB7 = !PORTBbits.RB7; // inverte o estado da porta RB7
            TMR0 = 0x6D84; //recarrega o inicio do timer0   28036  
            //TMR0L = 0x84; // recarrega o inicio do timer0   28036  
            //TMR0H = 0x6D; // recarrega o inicio do timer0   28036    
            TMR0IF = 0;       
        }     
        if(TMR1IF == 1)
        {                   
            PORTBbits.RB6 = !PORTBbits.RB6; // inverte o estado da porta RB6
            TMR1 = 0xFFF6; // pré-carga 65516
            //TMR1L = 0xFB; // recarrega o inicio do timer1   246
            //TMR1H = 0xFF; // recarrega o inicio do timer1   246
            TMR1IF = 0;
            segundos++;
            //if(segundos > 59){
            //    segundos = 0;
            //}
            pos_numero(segundos, 3);

            
        }
        if(TMR3IF == 1)
        {     
                PORTBbits.RB5 =  !PORTBbits.RB5; // inverte o estado da porta RB6
                TMR3 = 0xFDA8; // recarrega o inicio do timer1   246
                TMR3IF = 0;
                minutos++;
            
                segundos = 0;
                PosicaoCursorLCD(2,11);  
                EscreveInteiroLCD(0);
                
                pos_numero(minutos, 2);
                //PosicaoCursorLCD(2,8);
                //EscreveInteiroLCD(minutos);
                //contador = 0;

            
        } 
        if(minutos >= 60 /*TMR1IF == 1*/)
        {            
   
            horas++;
            if(horas > 23){
                horas = 0;
            }
            
            minutos = 0;
            PosicaoCursorLCD(2,8);  
            EscreveInteiroLCD(0);
            pos_numero(horas, 1);
            //PosicaoCursorLCD(2,5);
            //EscreveInteiroLCD(horas);
            
        }   
    }
}


/******************************************************************************               
* Funcao:   delay_ms(unsigned int delaytime)
* Entrada:  unsigned int delaytime - recebe valores de 0 a 65536
* Saida:    Nenhuma (void)
* Descricao: Gera um atraso de tempo conforme o valor recebido de delaytime
             O tempo interno é baseado no delay 1 ms. Assim, a cada loop temos o
 *           decremento da variável delaytime, até que ele atinja zero. Exemplo:
 *           se o delaytime = 500 a função terminará e retornará para o programa
 *           principal após 500 ms.
/******************************************************************************/


void delay_ms(unsigned int tempodeatraso)
{
    while(--tempodeatraso){
        __delay_ms(1); //Gera um atraso de 1ms
    }
}

void pos_numero(unsigned char valor, unsigned char casa)
{
    switch(casa){
        case 3: 
            if(valor <10){
                PosicaoCursorLCD(2,12);                  
            }else{
                PosicaoCursorLCD(2,11);  
            }
            EscreveInteiroLCD(valor);
            break;      
        case 2: 
            if(valor <10){
                PosicaoCursorLCD(2,9);   
            }else{
                PosicaoCursorLCD(2,8);  
            }
            EscreveInteiroLCD(valor);
            break;   
        case 1: 
            if(valor <10){
                PosicaoCursorLCD(2,6);                 
            }else{
                PosicaoCursorLCD(2,5);  
            }
            EscreveInteiroLCD(valor);
            break;  
    }

}
