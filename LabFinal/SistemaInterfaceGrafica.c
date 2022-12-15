/*
* Sistema de Interface Grafica
*/
#include "SistemaInterfaceGrafica.h"

extern tContext sContext;

extern TX_QUEUE display_queue;
ULONG display_message;

void interfaceGraficaThreadFxn(ULONG thread_input)
{

  while(1)
  {
    /* Verifica se existem mensagens na fila */
    UINT status = tx_queue_receive(&display_queue, &display_message, TX_WAIT_FOREVER);
    /* Atualiza a interface grafica */
  }
}

void displayStatus(UCHAR *temp_atual, UCHAR *temp_dsj, UCHAR *vent_vel, UCHAR *valv_temp, UCHAR *saida){
    GrContextInit(&sContext, &g_sCfaf128x128x16);
	
    GrFlush(&sContext);
    GrContextFontSet(&sContext, g_psFontFixed6x8);
	
    GrContextForegroundSet(&sContext, ClrWhite);
    GrContextBackgroundSet(&sContext, ClrBlack);
	
    GrStringDraw(&sContext,"T Atual:", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
    GrStringDraw(&sContext,"T Dsj:", -1, 80, (sContext.psFont->ui8Height+2)*0, true);
    GrStringDraw(&sContext, temp_atual, -1, 0, (sContext.psFont->ui8Height+2)*1, true);
    GrStringDraw(&sContext,"---------------------", -1, 0, (sContext.psFont->ui8Height+2)*2, true);
}
