/*
* Sistema de Monitoramento
*/
#ifndef __SisMonitor_H__
#define __SisMonitor_H__

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/adc.h"
#include "tx_api.h"
#include "gpio.h"

void monitoramentoThreadFxn(ULONG thread_input);
#endif //__SisMonitor_H__