/** @file main.c
*
*  Arquivo principal para o laboratorio 2 de sistemas embarcados.
*
*/

#include "gpio.h"
#include "system.h"
#include "driverlib/interrupt.h"
#include <stdio.h>

volatile uint32_t ui32ContTempo = 0;

int main(void)
{
    uint8_t running = 1;
    volatile uint32_t clocks;
    volatile uint32_t tempo;
    IntMasterDisable();
    vSYSTEM_Init();
    vGPIO_Init();
    SysCtlDelay(SYSTEM_CLOCK/10 * 5);
    vGPIO_SetLED1(LED_ON);
    ui8GPIO_SetSwitchFlag(0);
    ui32ContTempo = 0;
    IntMasterEnable();
    //
    // Loop Forever
    //
    while(1)
    {
      if(!(ui8GPIO_GetSwitchFlag()==0 && ui32ContTempo<30000) && running)
      {
        if(ui8GPIO_GetSwitchFlag()==1)
        {
          vGPIO_SetLED1(LED_OFF);
          clocks = ui32ContTempo*4;
          tempo = ui32ContTempo/10;
          printf("Numero de clocks: %u k\n", clocks);
          printf("Tempo de reacao: %u ms\n", tempo);
          running = 0;
        }
        else
        {
          vGPIO_SetLED1(LED_OFF);
          printf("Falhou!\n");
          running = 0;
        }
      }
      
        
    }
}