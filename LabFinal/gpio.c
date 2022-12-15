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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL))
    {
    }
    
    /* Configuracao USER_SWITCH */
    GPIOIntDisable(GPIO_PORTJ_BASE, USER_SWITCH);
    GPIOIntTypeSet(GPIO_PORTJ_BASE, USER_SWITCH, GPIO_FALLING_EDGE);
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, (USER_SWITCH));
    GPIOPadConfigSet(GPIO_PORTJ_BASE, USER_SWITCH, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTJ_BASE, USER_SWITCH);
    
    GPIOIntDisable(GPIO_PORTJ_BASE, USER_SWITCH2);
    GPIOIntTypeSet(GPIO_PORTJ_BASE, USER_SWITCH2, GPIO_FALLING_EDGE);
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, (USER_SWITCH2));
    GPIOPadConfigSet(GPIO_PORTJ_BASE, USER_SWITCH2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTJ_BASE, USER_SWITCH2);
    
    IntEnable(INT_GPIOJ);
    
    /* Configuracao USER_SWITCH da BoosterPack*/
    GPIOIntDisable(GPIO_PORTL_BASE, GPIO_PIN_1);
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_1, GPIO_FALLING_EDGE);
    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_1);
    
    GPIOIntDisable(GPIO_PORTL_BASE, GPIO_PIN_2);
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);
    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_2);
    
    IntEnable(INT_GPIOL);
}