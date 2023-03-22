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
void display_on_LCD(uint8_t count);
void init_LEDs(void);
void display_on_LEDs(uint8_t count);
void delay(unsigned int microseconds);
void init_switches(void);
void InitExternalInterrupts(void);
void EXTI2_3_IRQHandler(void);


// MAIN FUNCTION -------------------------------------------------------------|

uint8_t count = 0;
uint8_t display_on = 0;

void main(void)
{
	init_LEDs();
    init_LCD();
    init_switches();
    InitExternalInterrupts();


    while(1)
    {
        if (((GPIOA->IDR & GPIO_IDR_1) == 0) && display_on)
        {
            if (count < 255)
            {
                count++;
            }
            display_on_LEDs(count);
            display_on_LCD(count);
            delay(50000);
        }
        else if (((GPIOA->IDR & GPIO_IDR_2) == 0) && display_on)
        {
            if (count > 0)
            {
                count--;
            }
            display_on_LEDs(count);
            display_on_LCD(count);
            delay(50000);
        }
        else if ((GPIOA->IDR & GPIO_IDR_3) == 0)
        {
            if (display_on)
            {
                // turn off display and LEDs
                display_on = 0;
                GPIOB->ODR = 0;
                lcd_command(CLEAR);
            }
            else
            {
                // turn on display and LEDs
            	count = 0;
                display_on = 1;
                display_on_LEDs(count);
                display_on_LCD(count);
            }
            delay(50000);
        }
    }
}


// OTHER FUNCTIONS -----------------------------------------------------------|


void display_on_LCD(uint8_t count)
{
              lcd_command(CLEAR);
              char str[4];
              sprintf(str,"%d", count);
              lcd_putstring(str);
              delay(10000);

}
/* -----------------------------------------------------------*/
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
/* -----------------------------------------------------------*/

void display_on_LEDs(uint8_t count){

	GPIOB->ODR = count;
}

/* -----------------------------------------------------------*/

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
/* -----------------------------------------------------------*/
void InitExternalInterrupts(void){

    RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

    SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
    SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PA;
    SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PA;  // Set EXTI3 to PA3

    EXTI->IMR |= EXTI_IMR_MR3;
    EXTI->FTSR |= EXTI_FTSR_TR3;

    NVIC_EnableIRQ(EXTI2_3_IRQn);

}

/* -----------------------------------------------------------*/
void EXTI2_3_IRQHandler(void)
{
	EXTI->PR &= EXTI_PR_PR3;

}
/* -----------------------------------------------------------*/








