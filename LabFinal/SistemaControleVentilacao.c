/*
* Sistema de Controle de Ventilacao
*/
#include "SistemaControleVentilacao.h"
#include "enums.h"

extern TX_QUEUE vent_queue;
extern UINT vent_vel;

ULONG vent_message;
void controleVentilacaoThreadFxn(ULONG thread_input)
{

  while(1)
  {
    /* Verifica se existem mensagens na fila */
    UINT status = tx_queue_receive(&vent_queue, &vent_message, TX_WAIT_FOREVER);
    while(status == TX_SUCCESS)
    { 
        /* Altera a velocidade do ventilador de acordo */
        vent_vel = vent_message;
        tx_queue_receive(&vent_queue, &vent_message, TX_NO_WAIT);
    }
  }
}