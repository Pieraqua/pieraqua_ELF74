/** @file main.c
*
*  Arquivo principal para o laboratorio 2 de sistemas embarcados.
*
*/

#include "gpio.h"
#include "system.h"
#include <stdio.h>

volatile uint32_t ui32ContTempo = 0;

int main(void)
{
    vSYSTEM_Init();
    vGPIO_Init();
    ui8GPIO_SetSwitchFlag(0);
    vGPIO_SetLED1(LED_ON);
    ui32ContTempo = 0;
    //
    // Loop Forever
    //
    while(1)
    {
      if(!(ui8GPIO_GetSwitchFlag()==0 && ui32ContTempo<30000))
      {
        if(ui8GPIO_GetSwitchFlag()==1)
        {
          printf("Numero de clocks: %d\n", ui32ContTempo*100);
          printf("Tempo de reacao: %d ms\n", ui32ContTempo/10);
          while(1);
        }
        else
        {
          printf("Falhou!\n");
          while(1);
        }
      }
      
        
    }
}