
#include "tx_api.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "lab6_gpio.h"

#ifndef NULL
#define NULL 0
#endif

/* Clock do sistema */
#define SYSTEM_CLK 40000000

/* Tamanho de stack padrao de stack */
#define THREAD_STACK_SIZE 256

/* Informacoes de auto start */
#define AUTOSTART_0 TX_AUTO_START
#define AUTOSTART_1 TX_AUTO_START
#define AUTOSTART_2 TX_AUTO_START

/* Informacoes de time slice */
#define TIMESLICE_0 TX_NO_TIME_SLICE
#define TIMESLICE_1 TX_NO_TIME_SLICE
#define TIMESLICE_2 TX_NO_TIME_SLICE
 
TX_THREAD               thread_0;
TX_THREAD               thread_1;
TX_THREAD               thread_2;

CHAR thread0_stack[THREAD_STACK_SIZE];
CHAR thread1_stack[THREAD_STACK_SIZE];
CHAR thread2_stack[THREAD_STACK_SIZE];

void thread0_entry(ULONG thread_input);

int main()
{   
  /* Please refer to Chapter 6 of the ThreadX User Guide for a complete
       description of this demonstration.  */
  
    //
    // Run from the PLL at 40 MHz.
    // Note: SYSCTL_CFG_VCO_240 is a new setting provided in TivaWare 2.2.x and
    // later to better reflect the actual VCO speed due to SYSCTL#22.
    //
    //ui32SysClock = 
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                       SYSCTL_OSC_MAIN |
                                       SYSCTL_USE_PLL |
                                       SYSCTL_CFG_VCO_240), SYSTEM_CLK);
    
    vGPIO_Init();
    
    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
  
    /* Nao deveria chegar aqui */
    return 0;
}

/* Parametros passados como: */
/* 00 00000000000000 0000000000000000 */
/* LED    PERIODO   TEMPO DE EXECUCAO */
#define EXECTIME_0  300
#define PERIODO_0   1000
#define LED_THREAD0 1

#define EXECTIME_1  500
#define PERIODO_1   1500
#define LED_THREAD1 2

#define EXECTIME_2  800
#define PERIODO_2   4000
#define LED_THREAD2 3

/* Define what the initial system looks like.  */
void    tx_application_define(void *first_unused_memory)
{



#ifdef TX_ENABLE_EVENT_TRACE
    tx_trace_enable(trace_buffer, sizeof(trace_buffer), 32);
#endif

    tx_thread_create(&thread_0, "thread 0", thread0_entry, 
                     (EXECTIME_0 + (PERIODO_0<<16) + (LED_THREAD0<<30)),  
            thread0_stack, THREAD_STACK_SIZE, 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    tx_thread_create(&thread_1, "thread 1", thread0_entry, 
                     (EXECTIME_1 + (PERIODO_1<<16) + (LED_THREAD1<<30)),  
            thread0_stack, THREAD_STACK_SIZE, 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    tx_thread_create(&thread_2, "thread 2", thread0_entry, 
                     (EXECTIME_2 + (PERIODO_2<<16) + (LED_THREAD2<<30)),  
            thread0_stack, THREAD_STACK_SIZE, 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);

}


void thread0_entry(ULONG thread_input)
{
  /* Setup */
  uint8_t led = thread_input >> 30;
  uint8_t periodo = ((thread_input - (led<<30)) >> 16);
  uint8_t tempo_execucao = (thread_input - (led<<30) - (periodo<<16));
  /* Main loop */
  while(1)
  {}
}


