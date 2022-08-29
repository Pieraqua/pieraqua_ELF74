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
    IntMasterDisable();
    vSYSTEM_Init();
    vGPIO_Init();
    ui8GPIO_SetSwitchFlag(0);
    vGPIO_SetLED1(LED_ON);
    SysCtlDelay(SYSTEM_CLOCK/10 * 5);
    vGPIO_SetLED1(LED_ON);
    ui32ContTempo = 0;
    IntMasterEnable();
    //
    // Loop Forever
    //    
    while(1)
    {
      #ifdef __TESTE_ENABLE
        if(ui32ContTempo%10000)
        {
          vGPIO_BlinkLED();
          ui8GPIO_SetSwitchFlag(1);
          ui8GPIO_SetSwitchFlag(0);
        }
      #endif //__TESTE_ENABLE
      if(!(ui8GPIO_GetSwitchFlag()==0 && ui32ContTempo<30000) && running)
      {
        if(ui8GPIO_GetSwitchFlag()==1)
        {
          #ifdef __DEBUG_ENABLE
            printf("botao pressionado\n");
          #endif //__DEBUG_ENABLE
          uint32_t nclocks = ui32ContTempo*100;
          uint32_t tempo = ui32ContTempo/10;
          printf("Numero de clocks: %u\n", nclocks);
          printf("Tempo de reacao: %u ms\n", tempo);
          vGPIO_SetLED1(LED_OFF);
          running = 0;
        }
        else
        {
          printf("Falhou!\n");
          vGPIO_SetLED1(LED_OFF);
          running = 0;
        }
      }
      
        
    }
}