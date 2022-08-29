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
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, (USER_SWITCH));
    
}