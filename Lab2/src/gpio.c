/**
*   @file gpio.c
*
*   @brief Arquivo de configuracao das funcionalidades de gpio do projeto.
*/

#include "gpio.h"

/**
* Inicializa as portas GPIO utilizadas.
*/
void vGPIO_Init()
{
    //
    // Enable and wait for the port to be ready for access
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION))
    {
    }
    
    //
    // Configure the GPIO port for the LED operation.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (USER_LED1));
    GPIOPinTypeGPIOOutput(GPIO_PORTJ_BASE, (USER_SWITCH));
    
}
      
/**
* @brief Inverte o estado (pisca) o USER_LED1.
*/
void vGPIO_BlinkLED()
{
    static uint8_t ui8LedStatus = 0;
  
    if(ui8LedStatus)
      GPIOPinWrite(GPIO_PORTN_BASE, (USER_LED1), 0);
    else
      GPIOPinWrite(GPIO_PORTN_BASE, (USER_LED1), USER_LED1);

    ui8LedStatus = !ui8LedStatus;
}