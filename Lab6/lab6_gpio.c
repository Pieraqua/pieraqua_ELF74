/**
*   @file gpio.c
*
*   @brief Arquivo de configuracao das funcionalidades de gpio do projeto.
*/

#include "lab6_gpio.h"

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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }
    
    /* Configuracao USER_LED1 */
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (USER_LED1));
    /* Configuracao USER_LED2 */
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (USER_LED2));
    /* Configuracao USER_LED3 */
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, (USER_LED3));
}
      
/**
* @brief Inverte o estado (pisca) o led indicado pelo input.
*/
void vGPIO_BlinkLED(led_num)
{
    static uint8_t ui8LedStatus = 0;
  
    if(ui8LedStatus)
      //if (led_num != USER_LED3)
        GPIOPinWrite(GPIO_PORTN_BASE, (led_num), 0);
      //else
        //GPIOPinWrite(GPIO_PORTF_BASE, (led_num), 0);
    else
      //if (led_num != USER_LED3)
        GPIOPinWrite(GPIO_PORTN_BASE, (led_num), led_num);
      //else 
        //GPIOPinWrite(GPIO_PORTF_BASE, (led_num), led_num);
      
    ui8LedStatus = !ui8LedStatus;
}

