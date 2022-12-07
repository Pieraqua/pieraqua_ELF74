/*
* Sistema de Controle de Temperatura
*/
#include "SistemaControleTemperatura.h"

extern float temp_atual;
extern float temp_des;

extern TX_QUEUE temp_queue;
extern TX_QUEUE med_queue;
ULONG temp_message;

UINT temp_atual;
UINT temp_des;

void controleTempThreadFxn(ULONG thread_input)
{

  while(1)
  {
    /* Verifica se existem dados novos */
    UINT status = tx_queue_receive(&temp_queue, &temp_message, TX_NO_WAIT);
    while(status == TX_SUCCESS)
    {
      /* Consome os dados */
      temp_des = temp_message;
      status = tx_queue_receive(&temp_queue, &temp_message, TX_NO_WAIT);
    }
    
    status = tx_queue_receive(&med_queue, &temp_message, TX_NO_WAIT);
    while(status == TX_SUCCESS)
    {
      /* Consome os dados */
      temp_atual = temp_message;
      
      status = tx_queue_receive(&med_queue, &temp_message, TX_NO_WAIT);
    }
    /* Dados de monitoramento e configuracao - temperatura desejada e atual */
    
    
    /* Faz a regulagem das valvulas conforme os dados novos */
    tx_thread_sleep(1000);
    
  }
}