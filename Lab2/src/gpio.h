/**
* @file gpio.h
* @brief Arquivo de configuracao das funcionalidades gpio do projeto.
*/

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#define USER_LED1 GPIO_PIN_0
#define USER_LED1 GPIO_PIN_0

/**
* Inicializa as portas GPIO utilizadas.
*/
void vGPIO_Init();