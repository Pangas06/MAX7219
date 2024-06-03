#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "daughterboard.h"
#include "main.h"
#include "milis.h"
//#include "delay.h"
//#include "uart1.h"
#include "max7219.h"

#define DIN_PORT GPIOB
#define DIN_PIN GPIO_PIN_5

#define DIN_PORT GPIOB
#define DIN_PIN GPIO_PIN_4

#define DIN_PORT GPIOB
#define DIN_PIN GPIO_PIN_3

#define DIN_PORT 	GPIOB
#define DIN_PIN 	GPIO_PIN_5
#define CS_PORT 	GPIOB
#define CS_PIN 		GPIO_PIN_4
#define CLK_PORT 	GPIOB
#define CLK_PIN 	GPIO_PIN_3

void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    GPIO_Init(DIN_PORT, DIN_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CS_PORT, CS_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
    GPIO_Init(CLK_PORT, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);


    init_milis();
    //init_uart1();
}

void display(uint8_t adress, uint8_t data){
    uint8_t mask;
    LOW(CS);   //začátek přenosu
    /*pošlu adresu*/
    //mask = 128;
    mask = 1<<7;
    //mask = 0b10000000;

    while (mask) {
        
        if(adress & mask) {
            HIGH(DIN);  
        }else{
            LOW(DIN);
        }

        HIGH(CLK);
        
        mask = mask >> 1;

        LOW(CLK);
    }

    mask = 1<<7;
    /*pošlu data*/
    while (mask) {
        
        if(data & mask) {
            HIGH(DIN);   
        }else{
            LOW(DIN);
        };

        HIGH(CLK);
        
        mask = mask >> 1;

        LOW(CLK);
    }

    HIGH(CS);   //konec přenosu
}

int main(void)
{
  
    uint32_t time = 0;

    init();

    display(DECODE_MODE, 0b11111111);
    display(SCAN_LIMIT, 7);
    display(INTENSITY, 1);
    display(DISPLAY_TEST, DISPLAY_TEST_OFF);
    display(SHUTDOWN, SHUTDOWN_ON);
    display(DIGIT0, 0xF);
    display(DIGIT1, 0xF);
    display(DIGIT2, 0xF);
    display(DIGIT3, 0xF);
    display(DIGIT4, 0xF);
    display(DIGIT5, 0xF);
    display(DIGIT6, 0xF);
    display(DIGIT7, 0xF);
    int8_t number = 0; 

    while (1) {
        if (milis() - time > 333) {
            time = milis();
            display(DIGIT0, number++);

        }
        //delay_ms(333);
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
