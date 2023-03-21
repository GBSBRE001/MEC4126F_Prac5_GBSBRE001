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
void display_on_LEDs(uint8_t count);
void delay(unsigned int microseconds);


// MAIN FUNCTION -------------------------------------------------------------|

void main(void)
{
	//init_LEDs();
    init_LCD();

    while(1)
    {
    	display_on_LCD();
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









