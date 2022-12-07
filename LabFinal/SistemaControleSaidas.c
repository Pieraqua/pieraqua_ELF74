/*
* Sistema de Controle Saidas
*/
#include "SistemaControleSaidas.h"

extern TX_QUEUE saida_queue;

ULONG saida_message;
void controleSaidaThreadFxn(ULONG thread_input)
{

  while(1)
  {
    /* Verifica se existem dados novos na notificacao */
    UINT status = tx_queue_receive(&saida_queue, &saida_message, TX_WAIT_FOREVER);
    /* Atualiza as informacoes internas */
    while(status == TX_SUCCESS){
        
      status = tx_queue_receive(&saida_queue, &saida_message, TX_NO_WAIT);
    }
    /* Envia os dados para as tarefas interessadas */
  }
}