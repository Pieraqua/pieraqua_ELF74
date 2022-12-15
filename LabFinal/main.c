#include "tx_api.h"
#include "SistemaConfiguracao.h"
#include "SistemaControleSaidas.h"
#include "SistemaControleTemperatura.h"
#include "SistemaControleVentilacao.h"
#include "SistemaInterfaceGrafica.h"
#include "SistemaMonitoramento.h"    
#include "system.h"
#include "gpio.h"
#include "driverlib/interrupt.h"
#include "enums.h"

/* Threads presentes no sistema*/
TX_THREAD config;
TX_THREAD saida;
TX_THREAD temp;
TX_THREAD vent;
TX_THREAD display;
TX_THREAD monitor;
TX_THREAD main_thread;

/* Filas presentes no sistema */
TX_QUEUE config_queue;
TX_QUEUE temp_queue;
TX_QUEUE med_queue;
TX_QUEUE vent_queue;
TX_QUEUE saida_queue;
TX_QUEUE display_queue;
TX_QUEUE monitor_queue;

/* Pilhas das threads */
UCHAR config_stack[1024];
UCHAR saida_stack[1024];
UCHAR temp_stack[1024];
UCHAR vent_stack[1024];
UCHAR display_stack[1024];
UCHAR monitor_stack[1024];
UCHAR config_queue_mem[1024];
UCHAR temp_queue_mem[1024];
UCHAR med_queue_mem[1024];
UCHAR vent_queue_mem[1024];
UCHAR saida_queue_mem[128];
UCHAR display_queue_mem[1024];
UCHAR monitor_queue_mem[1024];
UCHAR main_thread_mem[1024];

/* Handler da thread principal */
void mainThreadEntry(ULONG thread_input);

/* Define buffer de evento */
#ifdef TX_ENABLE_EVENT_TRACE
UCHAR   trace_buffer[0x10000];
#endif

UINT vent_vel = 0;
UINT temp_des;
UINT temp_atual;
/* Contexto para usar display */
tContext sContext;

enSaidas saida_atual;
/* saida 0: nenhuma 
   saida 1: pes
   saida 2: painel
   saida 3: vidro
   saida 4: todas*/

int main()
{
    volatile uint32_t clocks;
    volatile uint32_t tempo;
    IntMasterDisable();
    vSYSTEM_Init();
    vGPIO_Init();
    IntMasterEnable();
    //Initialize LCD
    cfaf128x128x16Init();
    
    SysCtlDelay(SYSTEM_CLOCK/10 * 5);
    
    
    tx_kernel_enter();
    
    return 0;
}

/* Define o sistema inicial*/
void    tx_application_define(void *first_unused_memory)
{

#ifdef TX_ENABLE_EVENT_TRACE
    tx_trace_enable(trace_buffer, sizeof(trace_buffer), 32);
#endif
    /* Cria a thread principal*/
    tx_thread_create(&main_thread, "main_thread", mainThreadEntry, 0,  
            main_thread_mem, sizeof(main_thread_mem), 
            1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);

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
    tx_queue_create(&temp_queue, "temp queue", TX_1_ULONG, temp_queue_mem, sizeof(temp_queue_mem));
    tx_queue_create(&med_queue, "med queue", TX_1_ULONG, med_queue_mem, sizeof(med_queue_mem));
    tx_queue_create(&vent_queue, "vent queue", TX_1_ULONG, vent_queue_mem, sizeof(vent_queue_mem));
    tx_queue_create(&saida_queue, "saida queue", TX_1_ULONG, saida_queue_mem, sizeof(saida_queue_mem));
    tx_queue_create(&display_queue, "display queue", TX_4_ULONG, display_queue_mem, sizeof(display_queue_mem));
    tx_queue_create(&monitor_queue, "monitor queue", TX_1_ULONG, monitor_queue_mem, sizeof(monitor_queue_mem));
    
}

void mainThreadEntry(ULONG thread_input){}
