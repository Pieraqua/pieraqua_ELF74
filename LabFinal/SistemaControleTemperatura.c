/*
* Sistema de Controle de Temperatura
*/
#include "SistemaControleTemperatura.h"

extern TX_QUEUE temp_queue;
extern TX_QUEUE valv_queue;
extern TX_QUEUE monitor_queue;
ULONG temp_message;


void controleTempThreadFxn(ULONG thread_input)
{

  UINT temp_atual;
  UINT temp_des;
  UINT temp_valv;
  UINT valv_quente;
  UINT valv_fria;
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
    
    status = tx_queue_receive(&monitor_queue, &temp_message, TX_NO_WAIT);
    while(status == TX_SUCCESS)
    {
      /* Consome os dados */
      temp_atual = temp_message;
      
      status = tx_queue_receive(&monitor_queue, &temp_message, TX_NO_WAIT);
    }
    /* Dados de monitoramento e configuracao - temperatura desejada e atual */
    
    
    /* Faz a regulagem das valvulas conforme os dados novos */
    /* Esquentando */
    if (temp_atual < temp_des){
        temp_valv = temp_des + 20;
    }
    
    /* Resfriando */
    else if (temp_atual > temp_des){
        temp_valv = temp_des - 20;
    }
    /* temp_atual == temp_des*/
    else {
        temp_valv = temp_des;
    }
    
    /* Proporcao de aberturas das valvulas */
    valv_fria = (4000 - 100*temp_valv)/25;
    valv_quente = 100 - valv_fria;
    
    tx_queue_send(&valv_queue, &temp_valv, TX_NO_WAIT);
    
    tx_thread_sleep(1000);
    
  }
}