/**
* @file gpio.h
* @brief Arquivo de configuracao das funcionalidades gpio do projeto.
*/

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#define USER_LED1 GPIO_PIN_0 //PN0
#define USER_LED2 GPIO_PIN_1 //PN1
#define USER_SWITCH GPIO_PIN_0 //PJ0

typedef enum{
    LED_OFF = 0,
    LED_ON = 0xFF
}enLEDState;

/**
* Inicializa as portas GPIO utilizadas.
*/
void vGPIO_Init();

/**
* @brief Inverte o estado (pisca) o USER_LED1.
*/
void vGPIO_BlinkLED();

/**
* @brief Retorna o estado da flag do user_switch
*/
uint8_t ui8GPIO_GetSwitchFlag();

/**
* @brief Seta o estado do USER_LED1.
*/
void vGPIO_SetLED1(enLEDState val);

/**
* @brief Seta o estado da flag do user_switch para @p val.
*/
void ui8GPIO_SetSwitchFlag(uint8_t val);

