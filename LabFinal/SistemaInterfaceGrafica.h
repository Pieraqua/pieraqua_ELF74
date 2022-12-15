/*
* Sistema de Interface Grafica
*/
#ifndef __SisIntGraf_H__
#define __SisIntGraf_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "grlib/grlib.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "cfaf128x128x16.h"
#include "tx_api.h"

void displayStatus(UCHAR *temp_atual, UCHAR *temp_dsj, UCHAR *vent_vel, UCHAR *valv_temp, UCHAR *saida);
void interfaceGraficaThreadFxn(ULONG thread_input);
#endif //__SisIntGraf_H__