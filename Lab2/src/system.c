/**
* @file system.c
* @brief Arquivo de configuracao das funcionalidades de sistema (clock e systick).
*/

/**
* @brief Inicializa o clock do sistema e o SysTick.
*/
void vSYSTEM_Init()
{
    uint32_t ui32SysClock;

    //
    // Run from the PLL at 40 MHz.
    // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
    // later to better reflect the actual VCO speed due to SYSCTL#22.
    //
    ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), 40000000);

  /* Desabilita o systick (boas praticas) */
    SysTickDisable();

    /* Configura o Systick para interromper com a funcao desejada */
    SysTickIntRegister(systick_tick);
    
    /* Configura o periodo do systick para 1ms */
    /* SysClock ticks = 1s, SysClock ticks / 1000 = 1ms */
    SysTickPeriodSet(ui32SysClock/1000);
    
    /* Ativa o systick */
    SysTickEnable();
    
    /* Habilita a interrupcao do systick */
    SysTickIntEnable();
      
}
