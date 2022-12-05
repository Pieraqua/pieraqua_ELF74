#include "tx_api.h"
#include "SistemaConfiguracao.h"
#include "SistemaControleSaida.h"
#include "SistemaControleTempratura.h"
#include "SistemaControleVentilacao.h"
#include "SistemaInterfaceGrafica.h"
#include "SistemaMonitoramento.h"
#include "system.h"     
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"


/* Threads presentes no sistema*/
TX_THREAD config;
TX_THREAD saida;
TX_THREAD temp;
TX_THREAD vent;
TX_THREAD display;
TX_THREAD monitor;

/* Filas presentes no sistema */
TX_QUEUE config_queue;

/* Pilhas das threads */
UCHAR config_stack[1024];
UCHAR saida_stack[1024];
UCHAR temp_stack[1024];
UCHAR vent_stack[1024];
UCHAR display_stack[1024];
UCHAR monitor_stack[1024];
UCHAR config_queue_mem[1024];

/* Define buffer de evento */
#ifdef TX_ENABLE_EVENT_TRACE
UCHAR   trace_buffer[0x10000];
#endif

int main()
{
    volatile uint32_t clocks;
    volatile uint32_t tempo;
    IntMasterDisable();
    vSYSTEM_Init();
    vGPIO_Init();
    IntMasterEnable();
    
    SysCtlDelay(SYSTEM_CLOCK/10 * 5);
    
    
    
    
     /* Initializing ADC (MCLK/1/1) */
    ADC14_enableModule();
    ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
            0);
    /* Configuring ADC Memory (ADC_MEM0 A0/A1 Differential) in repeat mode
     * with use of external references */
    ADC14_configureSingleSampleMode(ADC_MEM0, true);
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_EXTPOS_VREFNEG_EXTNEG,
            ADC_INPUT_A0, true);
    /* Setting up GPIO pins as analog inputs (and references) */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN6 | GPIO_PIN5 | GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
    /* Enabling sample timer in auto iteration mode and interrupts*/
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
    ADC14_enableInterrupt(ADC_INT0);
    /* Enabling Interrupts */
    Interrupt_enableInterrupt(INT_ADC14);
    Interrupt_enableMaster();
    /* Triggering the start of the sample */
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
    
    
    tx_kernel_enter();
    
    return 0;
}

/* Define o sistema inicial*/
void    tx_application_define(void *first_unused_memory)
{

#ifdef TX_ENABLE_EVENT_TRACE
    tx_trace_enable(trace_buffer, sizeof(trace_buffer), 32);
#endif

    /* Cria a thread de configuracao */
    tx_thread_create(&config, "config", configThreadFxn, 0,  
            config_stack, sizeof(config_stack), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Cria a thread de saida */
    tx_thread_create(&saida, "saida", controleSaidaThreadFxn, 0,  
            saida_stack, sizeof(saida_stack), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Cria a thread de temperatura */
    tx_thread_create(&temp, "temp", controleTempThreadFxn, 0,  
            temp_stack, sizeof(temp_stack), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Cria a thread de ventilacao */
    tx_thread_create(&vent, "vent", controleVentilacaoThreadFxn, 0,  
            vent_stack, sizeof(vent_stack), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Cria a thread de display */
    tx_thread_create(&display, "display", interfaceGraficaThreadFxn, 0,  
            display_stack, sizeof(display_stack), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Cria a thread de monitoramento */
    tx_thread_create(&monitor, "monitor", monitoramentoThreadFxn, 0,  
            monitor_stack, sizeof(monitor_stack), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    
    /* Cria a fila utilizada pelo sistema de configuracao */
    tx_queue_create(&config_queue, "config queue", TX_1_ULONG, config_queue_mem, sizeof(config_queue_mem));
}

