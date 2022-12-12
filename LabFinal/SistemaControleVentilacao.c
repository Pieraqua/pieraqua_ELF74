/*
* Sistema de Controle de Ventilacao
*/
#include "SistemaControleVentilacao.h"

extern TX_QUEUE vent_queue;
extern UINT vent_vel;

ULONG vent_message[4];
void controleVentilacaoThreadFxn(ULONG thread_input)
{

  while(1)
  {
    /* Verifica se existem mensagens na fila */
    UINT status = tx_queue_receive(&vent_queue, vent_message, TX_WAIT_FOREVER);
    if (status == TX_SUCCESS && vent_message[0] == 1){
        if (vent_vel < 5){
            vent_vel++;
        }
        else if (status == TX_SUCCESS && vent_message[0] == 0){
            if (vent_vel > 0){
                vent_vel--;
            }
        }
    }
    /* Altera a velocidade do ventilador de acordo */
  }
}