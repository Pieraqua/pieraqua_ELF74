/**
* @file system.c
* @brief Arquivo de configuracao das funcionalidades de sistema (clock e systick).
*/

#include "system.h"

extern volatile uint32_t ui32ContTempo;
void vSYSTEM_Tick()
{
    if(ui32ContTempo < UINT32_MAX)
      ui32ContTempo++;
}

/**
* @brief Inicializa o clock do sistema e o SysTick.
*/
void vSYSTEM_Init()
{
    //uint32_t ui32SysClock;

    //
    // Run from the PLL at 40 MHz.
    // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
    // later to better reflect the actual VCO speed due to SYSCTL#22.
    //
    //ui32SysClock = 
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), SYSTEM_CLOCK);

    /* Desabilita o systick (boas praticas) */
    SysTickDisable();
    
    /* Configura o periodo do systick para 1ms */
    /* SysClock ticks = 1s, SysClock ticks / 1000 = 100us */
    SysTickPeriodSet(SYSTEM_CLOCK/100);
    
    /* Ativa o systick */
    SysTickEnable();
    
    /* Habilita a interrupcao do systick */
    SysTickIntEnable();
      
}
