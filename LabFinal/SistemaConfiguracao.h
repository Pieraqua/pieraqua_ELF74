/*
* Sistema de Configuracao
*/
#ifndef __SisConfig_H__
#define __SisConfig_H__

#include <stdint.h>
#include "tx_api.h"

void configThreadFxn(ULONG thread_input);
void config_queue_send_notify(TX_QUEUE *queue_ptr);
static void IntPushButtonHandler(void);


#endif //__SisConfig_H__