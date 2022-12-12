#include "tx_api.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "lab6_gpio.h"

#ifndef NULL
#define NULL 0
#endif

#define DEMO_BYTE_POOL_SIZE     9120

/* Define event buffer.  */

#ifdef TX_ENABLE_EVENT_TRACE
UCHAR   trace_buffer[0x10000];
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

/* Prioridades das threads*/
#define HIGH    0
#define MEDIUM  10
#define LOW     20

/* Define the ThreadX object control blocks...  */

TX_BYTE_POOL            byte_pool_0;

/* Define byte pool memory.  */

UCHAR                   byte_pool_memory[DEMO_BYTE_POOL_SIZE];
 
TX_THREAD               thread_0;
TX_THREAD               thread_1;
TX_THREAD               thread_2;

UCHAR thread0_stack[THREAD_STACK_SIZE];
UCHAR thread1_stack[THREAD_STACK_SIZE];
UCHAR thread2_stack[THREAD_STACK_SIZE];

void thread0_entry(ULONG thread_input);
void BlinkLEDTimes(int n_loops, int n_led);

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

#define LOOPS       5

/* Define what the initial system looks like.  */
void    tx_application_define(void *first_unused_memory)
{
  
  CHAR    *pointer = TX_NULL;
  
#ifdef TX_ENABLE_EVENT_TRACE
    tx_trace_enable(trace_buffer, sizeof(trace_buffer), 32);
#endif
    
    /* Create a byte memory pool from which to allocate the thread stacks.  */
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", byte_pool_memory, DEMO_BYTE_POOL_SIZE);
    
    /* Allocate the stack for thread 0.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, THREAD_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&thread_0, "thread 0", thread0_entry, 
                     (EXECTIME_0 + (PERIODO_0<<16) + (LED_THREAD0<<30)),  
            thread0_stack, THREAD_STACK_SIZE, 
            HIGH, 0, TIMESLICE_0, TX_AUTO_START);
    
    /* Allocate the stack for thread 1.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, THREAD_STACK_SIZE, TX_NO_WAIT);
    
    tx_thread_create(&thread_1, "thread 1", thread0_entry, 
                     (EXECTIME_1 + (PERIODO_1<<16) + (LED_THREAD1<<30)),  
            thread0_stack, THREAD_STACK_SIZE, 
            MEDIUM, 0, TIMESLICE_1, TX_AUTO_START);
    
    /* Allocate the stack for thread 2.  */
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, THREAD_STACK_SIZE, TX_NO_WAIT);
    
    tx_thread_create(&thread_2, "thread 2", thread0_entry, 
                     (EXECTIME_2 + (PERIODO_2<<16) + (LED_THREAD2<<30)),  
            thread0_stack, THREAD_STACK_SIZE, 
            LOW, 10, TIMESLICE_2, TX_AUTO_START);
    
    /* Release the block back to the pool.  */
    tx_block_release(pointer);
}


void thread0_entry(ULONG thread_input)
{
  /* Setup */
  uint8_t led = thread_input >> 30;
  uint8_t periodo = ((thread_input - (led<<30)) >> 16);
  uint8_t tempo_execucao = (thread_input - (led<<30) - (periodo<<16));
  /* Main loop */
  while(1)
  {
   
    BlinkLEDTimes(LOOPS, led);
    tx_thread_sleep(periodo-tempo_execucao);
  }
}

void BlinkLEDTimes(int n_loops, int n_led){
  static int loops = 0;
  for (;loops<n_loops; loops++){
    vGPIO_BlinkLED(n_led);}
}


