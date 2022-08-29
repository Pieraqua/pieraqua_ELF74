/** @file main.c
*
*  Arquivo principal para o laboratorio 2 de sistemas embarcados.
*
*/

#include "gpio.h"
#include "system.h"

int main(void)
{
    vSYSTEM_Init();
    vGPIO_Init();
    
    //
    // Loop Forever
    //
    while(1)
    {
        if(!ui32LedTimer)
        {
            blink_led_1();
            
            /* 100ms de periodo */
            ui32LedTimer = 100;
        }
    }
}