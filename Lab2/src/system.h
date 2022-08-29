/**
* @file system.h
* @brief Arquivo de configuracao do sistema e do SysTick.
*/

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

/**
* @brief Inicializa o clock do sistema e o SysTick.
*/
void vSYSTEM_Init();