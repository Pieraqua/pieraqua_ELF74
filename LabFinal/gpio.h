/**
* @file gpio.h
* @brief Arquivo de configuracao das funcionalidades gpio do projeto.
*/
#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c1294ncpdt.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"

#define USER_SWITCH GPIO_PIN_0 //PJ0
#define USER_SWITCH2 GPIO_PIN_1 //PJ1

/**
* Inicializa as portas GPIO utilizadas.
*/
void vGPIO_Init();


#endif //__GPIO_H__