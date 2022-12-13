/*
* Sistema de Controle Saidas
*/
#include "SistemaControleSaidas.h"
#include "enums.h"

extern TX_QUEUE saida_queue;

void controleSaidaThreadFxn(ULONG thread_input)
{
  ULONG saida_message = 0;
  while(1)
  {
    /* Verifica se existem dados novos na notificacao */
    UINT status = tx_queue_receive(&saida_queue, &saida_message, TX_WAIT_FOREVER);
    /* Atualiza as informacoes internas */
    while(status == TX_SUCCESS){
        
      status = tx_queue_receive(&saida_queue, &saida_message, TX_NO_WAIT);
    }
    
    /* Controla as saidas */
    
    
  }
}