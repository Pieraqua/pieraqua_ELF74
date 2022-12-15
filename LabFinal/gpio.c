/**
*   @file gpio.c
*
*   @brief Arquivo de configuracao das funcionalidades de gpio do projeto.
*/

#include "gpio.h"
#include "driverlib/adc.h"

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
    
    /* Configuracao USER_SWITCH do Joystick */
    GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_FALLING_EDGE);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_6);
    IntEnable(INT_GPIOC);
    
    /* Configuracao ADC (Joystick) */
    /* eixo x */
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);
    GPIOADCTriggerEnable(GPIO_PORTE_BASE, GPIO_PIN_3);
    /* eixo y */
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOADCTriggerEnable(GPIO_PORTE_BASE, GPIO_PIN_4);
    
    ADCSequenceConfigure(ADC1_BASE, 2, ADC_TRIGGER_TIMER, 0); 
    ADCSequenceStepConfigure(ADC1_BASE, 2, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC1_BASE, 2, 1, ADC_CTL_CH9 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC1_BASE, 2); 
    
}