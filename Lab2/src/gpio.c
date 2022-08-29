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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }
    
    //
    // Configure the GPIO port for the LED operation.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (USER_LED1));
    GPIOIntDisable(GPIO_PORTJ_BASE, 0x1FF);
    GPIOIntTypeSet(GPIO_PORTJ_BASE, USER_SWITCH, GPIO_FALLING_EDGE);
    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, (USER_SWITCH));
    GPIOIntEnable(GPIO_PORTJ_BASE, USER_SWITCH);
    
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

uint8_t ui8FlagSwitch = 0;

/**
* @brief Seta o estado da flag do user_switch para @p val.
*/
void ui8GPIO_SetSwitchFlag(uint8_t val)
{
    ui8FlagSwitch = val;
}

/**
* @brief Retorna o estado da flag do user_switch.
*/
uint8_t ui8GPIO_GetSwitchFlag()
{
    return ui8FlagSwitch;
}

/**
* @brief Interrupcao do botao que seta a flag de botao para 1.
*/
void vGPIO_IntSwitch()
{
    if(GPIOIntStatus(GPIO_PORTJ_BASE, true) == GPIO_INT_PIN_0)
    {
        ui8FlagSwitch = 1;
    }
    
    GPIOIntClear(GPIO_PORTJ_BASE, 0x1FF);
    
}