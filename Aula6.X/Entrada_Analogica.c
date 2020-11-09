/*******************************************************************************
 FileName:     Teste Entradas Analógicas - FATEC SANTO ANDRÉ
 Dependencies: Veja a seção de includes
 Processor:    PIC18F4550
 Compiler:     MPLAB X v3.65 + XC8 1.41
 Company:      FATEC Santo Andre
 Author:       Deivide Souza
 Date:         01/10/2020
 Software License Agreement: Somente para fins didáticos
 *******************************************************************************
 File Description: Este programa testa a entrada analógica
 Change History:
 1.0   01/10/2020  Versão inicial
 
*******************************************************************************/


// Includes do Compilador

#include<p18f4550.h>
#include<stdio.h>
#include<stdlib.h>

// Includes do Projeto

#include "Config.h"
#include "displayLCD.h"

// Protótipos das Funções 

void delay_ms(unsigned int temodeatraso);

// Define os apelidos das variáveis do PIC

#define RB7 PORTBbits.RB7


/******************************************************************************               
* Funcao:   void main(void)
* Entrada:  Nenhuma (void)
* Saida:    Nenhuma (void)
* Descricao: 
/******************************************************************************/


#include <xc.h>

void main(void) {
    
    const unsigned char Texto_0[]="FATEC STO. ANDRE";
    const unsigned char Texto_1[]="ENT. ANALOGICA  ";
    const unsigned char Texto_2[]="ADRESH =        ";
    const unsigned char Texto_3[]="ADRESL =        ";
    const unsigned char Texto_4[]="                ";
    const unsigned char Texto_5[]="AN0 =           ";
    
    unsigned int valorAN0 = 0;
    
    ADCON1 = 0b00001110; // define a entrada an0
    ADCON0 = 0b00000001; // configurado para ler an0
    ADCON2 = 0b10001110; // configura o ADCON2 - 0x8e - hexa
    
    
    //Configura e prepara o Display LCD
    
    ConfiguraLCD(); // prepara o display LCD 
    DesligaCursor();
    EscreveFraseRamLCD(Texto_0);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_1);
    
    delay_ms(5000);
    
    PosicaoCursorLCD(1,1);
    EscreveFraseRamLCD(Texto_1);
    PosicaoCursorLCD(2,1);
    EscreveFraseRamLCD(Texto_5);

    
    
    while(1)
    {
            ADCON0 = 0b00000011; // dispara a leitura do an0
            while(ADCON0bits.DONE){
                
            }
            /*PosicaoCursorLCD(1,9);
            EscreveInteiroLCD(ADRESH);
            PosicaoCursorLCD(2,9);
            EscreveInteiroLCD(ADRESL);
            delay_ms(1000);
            */
            
            valorAN0 = (ADRESH << 8) + ADRESL; // montar uma word
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD(Texto_4);
            PosicaoCursorLCD(2,1);
            EscreveFraseRamLCD(Texto_5);
            PosicaoCursorLCD(2,7);
            EscreveInteiroLCD(valorAN0);        
            delay_ms(1000);
    }
}
/******************************************************************************               
* Funcao:   delay_ms(unsigned int delaytime)
* Entrada:  unsigned int delaytime - recebe valores de 0 a 65536
* Saida:    Nenhuma (void)
* Descricao: Gera um atraso de tempo conforme o valor recebido de delaytime
             O tempo interno é baseado no delay 1 ms. Assim, a cada loop temos o
 *           decremento da variável delaytime, até que ele atinja zero. Exemplo:
 *           se o delyatime = 500 a função terminará e retornará para o programa
 *           principal após 500 ms.
/******************************************************************************/

void delay_ms(unsigned int tempodeatraso)
{
    while(--tempodeatraso){
        __delay_ms(1); //Gera um atraso de 1ms
    }
}