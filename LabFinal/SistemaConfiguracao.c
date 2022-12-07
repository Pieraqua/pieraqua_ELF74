/*
* Sistema de Configuracao
*/
#include "SistemaConfiguracao.h"

#include "gpio.h"
#include "enums.h"

extern TX_QUEUE config_queue;
extern UINT vent_vel;
ULONG last_message;

typedef enum
{
  cmdSaidaPes = 0,
  cmdSaidaVidro,
  cmdSaidaPainel,
  cmdSaidaDesligado,
  cmdVplus,
  cmdVminus,
  cmdTplus,
  cmdTminus
} enComandos;

typedef struct
{
  UINT temp;
  UINT vel;
  enSaidas saida;
  
} stConfig;

stConfig STCONFIG;

/*  */
void configThreadFxn(ULONG thread_input)
{

  while(1)
  {
    /* Verifica se existem dados novos na fila */
    UINT status = tx_queue_receive(&config_queue, &last_message, TX_NO_WAIT);
    while(status == TX_SUCCESS){
      
      /* Consome o ultimo comando */
      /* Interpreta o comando */
      switch(last_message)
      {
      case cmdSaidaPes:
        STCONFIG.saida = pes;
        tx_queue_send(&saida_queue);
        break;
      case cmdSaidaPainel:
        STCONFIG.saida = painel;
        tx_queue_send(&saida_queue);
        
        break;
      case cmdSaidaVidro:
        STCONFIG.saida = vidro;
        tx_queue_send(&saida_queue);
        
        break;
      case cmdSaidaDesligado:
        STCONFIG.saida = desligado;
        tx_queue_send(&saida_queue);
        
        break;
      case cmdVplus:
        if(STCONFIG.vel < 5)
          STCONFIG.vel += 1;
        tx_queue_send(&vent_queue);
        
        break;
      case cmdVminus:
        if(STCONFIG.vel > 0)
          STCONFIG.vel -= 1;
        tx_queue_send(&vent_queue);
        
        break;
      case cmdTplus:
        if(STCONFIG.temp < 300)
          STCONFIG.temp += 5;
        tx_queue_send(&temp_queue);
        
        break;
      case cmdTminus:
        if(STCONFIG.temp > 160)
          STCONFIG.temp -= 5;
        tx_queue_send(&temp_queue);
        break;
      }
      
      status = tx_queue_receive(&config_queue, &last_message, TX_NO_WAIT);
    }
    
    
    /* Envia as informacoes novas para as tarefas interessadas */
    
    /* Ha um tempo de 5s entre cada operacao*/
    tx_thread_sleep(5000);
  }
}

/*void config_queue_send_notify(TX_QUEUE *queue_ptr){
    UINT status = tx_queue_receive(&config_queue, &last_message, TX_WAIT_FOREVER);
    if (status == TX_SUCCESS){
        
    }
}*/

static void 
IntPushButtonHandler(void){
    /* Se for de PJ0 -> V+ */
    /* Se for de PJ1 -> V- */
    /* Se for de PJ4.33 -> T+ */
    /* Se for de PJ4.32 -> T- */
    if(GPIOIntStatus(GPIO_PORTJ_BASE, true) == GPIO_INT_PIN_0)
    {
        
    }
    
    GPIOIntClear(GPIO_PORTJ_BASE, 0x1FF);
    
}
