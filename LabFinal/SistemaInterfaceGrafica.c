/*
* Sistema de Interface Grafica
*/
#include "SistemaInterfaceGrafica.h"
#include "SistemaConfiguracao.h"

extern tContext sContext;

extern TX_QUEUE display_queue;
extern TX_QUEUE monitor_queue;
extern TX_QUEUE valv_queue;

void interfaceGraficaThreadFxn(ULONG thread_input)
{
  CHAR *vent_vel;
  CHAR *temp_des;
    CHAR *temp_atual;
    CHAR *valv_temp;
    CHAR *saida_display;
    ULONG display_message;
  while(1)
  {
    /* Verifica se existem mensagens na fila */
    UINT status = tx_queue_receive(&display_queue, &display_message, TX_NO_WAIT);
    if(status == TX_SUCCESS){
        /* Atualiza a interface grafica */
        stConfig *data = (stConfig*)&display_message;
        vent_vel = (char*)data->vel;
        temp_des = (char*)data->temp;
        saida_display = (char*)data->saida;
    }
    
    status = tx_queue_receive(&monitor_queue, &display_message, TX_NO_WAIT);
    if(status == TX_SUCCESS){
        temp_atual = (char*)&display_message;
    }
    status = tx_queue_receive(&valv_queue, &display_message, TX_NO_WAIT);
    
    if(status == TX_SUCCESS){
        valv_temp = (char*)&display_message;
    }          
    displayStatus(temp_atual, temp_des, vent_vel, valv_temp, saida_display);
  }
}

void displayStatus(UCHAR *temp_atual, UCHAR *temp_dsj, UCHAR *vent_vel, UCHAR *valv_temp, UCHAR *saida){
    GrContextInit(&sContext, &g_sCfaf128x128x16);
	
    GrFlush(&sContext);
    GrContextFontSet(&sContext, g_psFontFixed6x8);
	
    GrContextForegroundSet(&sContext, ClrWhite);
    GrContextBackgroundSet(&sContext, ClrBlack);
	
    GrStringDraw(&sContext,"T Atual:", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
    GrStringDraw(&sContext,"T Dsj:", -1, 50, (sContext.psFont->ui8Height+2)*0, true);
    GrStringDraw(&sContext, "T Valv:", -1, 90, (sContext.psFont->ui8Height+2)*0, true);
    GrStringDraw(&sContext, temp_atual, -1, 0, (sContext.psFont->ui8Height+2)*1, true);
    GrStringDraw(&sContext, temp_dsj, -1, 50, (sContext.psFont->ui8Height+2)*1, true);
    GrStringDraw(&sContext, valv_temp, -1, 90, (sContext.psFont->ui8Height+2)*1, true);
    GrStringDraw(&sContext,"---------------------", -1, 0, (sContext.psFont->ui8Height+2)*2, true);
    GrStringDraw(&sContext, "Velocidade:", -1, 0, (sContext.psFont->ui8Height+2)*3, true);
    GrStringDraw(&sContext, "Saida:", -1, 70, (sContext.psFont->ui8Height+2)*3, true);
    GrStringDraw(&sContext, vent_vel, -1, 0, (sContext.psFont->ui8Height+2)*4, true);
    GrStringDraw(&sContext, saida, -1, 0, (sContext.psFont->ui8Height+2)*4, true);
}
