// Description----------------------------------------------------------------|
/*
 * Initialises a struct with Name and Age data. Displays results on LEDs and
 * LCD.
 */
// DEFINES AND INCLUDES-------------------------------------------------------|

#define STM32F051                                                                                                                                                             //COMPULSORY
#include "stm32f0xx.h"                                                                                                                                                       //COMPULSORY
#include "lcd_stm32f0.h"
#include <stdio.h>


// FUNCTION DECLARATIONS -----------------------------------------------------|

void main(void);
void lcd_putstring(char * instring);
void display_on_LCD(uint8_t num);
void init_LEDs(void);
void display_on_LEDs(uint8_t number);
void delay(unsigned int microseconds);


// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{
	init_LEDs();
    init_LCD();

    while(1)
    {
    	display_on_LCD(5);
    	display_on_LEDs(12);
    }
}


// OTHER FUNCTIONS -----------------------------------------------------------|


void display_on_LCD(uint8_t num)
{
              lcd_command(CLEAR);
              char str[2];
              sprintf(str,"%d", num);
              lcd_putstring(str);
              delay(10000);

}

void init_LEDs(void)
{

	RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB -> MODER |= GPIO_MODER_MODER0_0;
	GPIOB -> MODER |= GPIO_MODER_MODER1_0;
	GPIOB -> MODER |= GPIO_MODER_MODER2_0;
	GPIOB -> MODER |= GPIO_MODER_MODER3_0;
	GPIOB -> MODER |= GPIO_MODER_MODER4_0;
	GPIOB -> MODER |= GPIO_MODER_MODER5_0;
	GPIOB -> MODER |= GPIO_MODER_MODER6_0;
	GPIOB -> MODER |= GPIO_MODER_MODER7_0;

}

void display_on_LEDs(uint8_t number){

	GPIOB->ODR = number;
}


void init_switches(void)
{
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIOA -> MODER &= ~GPIO_MODER_MODER1;
    GPIOA -> MODER &= ~GPIO_MODER_MODER2;
    GPIOA -> MODER &= ~GPIO_MODER_MODER3;

    GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR1_0;
    GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR2_0;
    GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR3_0;

}







