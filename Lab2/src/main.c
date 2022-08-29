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
        
    }
}