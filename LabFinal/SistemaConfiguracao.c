/*
* Sistema de Configuracao
*/
#include "SistemaConfiguracao.h"
#include "gpio.h"

extern TX_QUEUE config_queue;
extern UINT vent_vel;
ULONG last_message[4];

void configThreadFxn(ULONG thread_input)
{

  while(1)
  {
    /* Verifica se existem dados novos na fila */
    UINT status = tx_queue_send_notify(&config_queue, config_queue_send_notify);
    
    /* Consome o ultimo comando */
    
    /* Interpreta o comando */
    
    /* Envia as informacoes novas para as tarefas interessadas */
    /* Ha um tempo de 5s entre cada operacao*/
    tx_thread_sleep(5000);
  }
}

void config_queue_send_notify(TX_QUEUE *queue_ptr){
    UINT status = tx_queue_receive(&config_queue, last_message, TX_WAIT_FOREVER);
    if (status == TX_SUCCESS){
        
    }
}

static void 
IntPushButtonHandler(void){
    /* Se for de PJ0 -> V+ */
    /* Se for de PJ1 -> V- */
    /* Se for de PJ4.33 -> T+ */
    /* Se for de PJ4.32 -> T- */
    if(GPIOIntStatus(GPIO_PORTJ_BASE, true) == GPIO_INT_PIN_0)
    {
        
    }
    
    GPIOIntClear(GPIO_PORTJ_BASE, 0x1FF);
    
}
