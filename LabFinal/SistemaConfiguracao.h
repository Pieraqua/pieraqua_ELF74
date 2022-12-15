/*
* Sistema de Configuracao
*/
#ifndef __SisConfig_H__
#define __SisConfig_H__

#include <stdint.h>
#include "tx_api.h"
#include "enums.h"

void configThreadFxn(ULONG thread_input);
void config_queue_send_notify(TX_QUEUE *queue_ptr);
void IntPushButtonHandler(void);
void IntPushButtonBooster(void);

/* Estrutura com os dados que devem ser enviados para as tarefas */
typedef struct
{
  ULONG temp;
  ULONG vel;
  enSaidas saida;
  /* Ler a documentacao pra saber se precisa disso ou pode */
  /* usar tamanho customizado na queue */
  ULONG filler;
} stConfig;


#endif //__SisConfig_H__