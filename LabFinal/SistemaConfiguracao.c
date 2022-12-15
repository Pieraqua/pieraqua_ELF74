/*
* Sistema de Configuracao
*/
#include "SistemaConfiguracao.h"

#include "gpio.h"
#include "enums.h"

extern TX_QUEUE config_queue;
extern TX_QUEUE display_queue;
extern TX_QUEUE saida_queue;
extern TX_QUEUE vent_queue;
extern TX_QUEUE temp_queue;
extern UINT vent_vel;

typedef enum
{
  cmdSaidaPes = (ULONG)0,
  cmdSaidaVidro,
  cmdSaidaPainel,
  cmdSaidaDesligado,
  cmdVplus,
  cmdVminus,
  cmdTplus,
  cmdTminus
} enComandos;

void configThreadFxn(ULONG thread_input)
{
  stConfig STCONFIG;
  STCONFIG.saida = nenhuma;
  STCONFIG.vel = 0;
  STCONFIG.temp = 200;
  STCONFIG.filler = -1;
  enComandos last_message = cmdSaidaDesligado;
  
  
  while(1)
  {
    /* Verifica se existem dados novos na fila */
    UINT status = tx_queue_receive(&config_queue, &last_message, TX_WAIT_FOREVER);
    while(status == TX_SUCCESS){
      
      /* Consome o ultimo comando */
      /* Interpreta o comando */
      switch(last_message)
      {
      case cmdSaidaPes:
        STCONFIG.saida = pes;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      case cmdSaidaPainel:
        STCONFIG.saida = painel;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      case cmdSaidaVidro:
        STCONFIG.saida = vidro;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      case cmdSaidaDesligado:
        STCONFIG.saida = nenhuma;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      case cmdVplus:
        if(STCONFIG.vel < 5)
          STCONFIG.vel += 1;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      case cmdVminus:
        if(STCONFIG.vel > 0)
          STCONFIG.vel -= 1;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      case cmdTplus:
        if(STCONFIG.temp < 300)
          STCONFIG.temp += 5;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      case cmdTminus:
        if(STCONFIG.temp > 160)
          STCONFIG.temp -= 5;
        tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
        break;
      }
      
      /* Caso nao receba uma mensagem nova em 5 segundos, envia as configuracoes */
      /* para as tarefas interessadas */
      status = tx_queue_receive(&config_queue, &last_message, 5000);
    }
    
    
    /* Envia as informacoes novas para as tarefas interessadas */
    /* Podia tratar o caso de nao conseguir enviar uma mensagem, mas nao tem muito o que fazer */
    tx_queue_send(&saida_queue, &STCONFIG.saida, TX_NO_WAIT);
    tx_queue_send(&vent_queue, &STCONFIG.vel, TX_NO_WAIT);
    tx_queue_send(&temp_queue, &STCONFIG.temp, TX_NO_WAIT);
    tx_queue_send(&display_queue, &STCONFIG, TX_NO_WAIT);
  }
}

void 
IntPushButtonHandler(void){
    /* Se for de PJ0 -> V+ */
    /* Se for de PJ1 -> V- */
    if(GPIOIntStatus(GPIO_PORTJ_BASE, true) == GPIO_INT_PIN_0)
    {
        enComandos cmd = cmdVplus;
        tx_queue_send(&config_queue, &cmd, TX_NO_WAIT);
        GPIOIntClear(GPIO_PORTJ_BASE, GPIO_INT_PIN_0);
    }
    
    else if(GPIOIntStatus(GPIO_PORTJ_BASE, true) == GPIO_INT_PIN_1)
    {
        enComandos cmd = cmdVminus;
        tx_queue_send(&config_queue, &cmd, TX_NO_WAIT);
        GPIOIntClear(GPIO_PORTJ_BASE, GPIO_INT_PIN_1);
    }
    
}

void IntPushButtonBooster(void){
    /* Se for de PJ4.33 /PL1 -> T+ */
    /* Se for de PJ4.32 /PL2 -> T- */
    if(GPIOIntStatus(GPIO_PORTL_BASE, true) == GPIO_INT_PIN_1)
    {
        enComandos cmd = cmdTplus;
        tx_queue_send(&config_queue, &cmd, TX_NO_WAIT);
        GPIOIntClear(GPIO_PORTL_BASE, GPIO_INT_PIN_1);
    }
    
    else if(GPIOIntStatus(GPIO_PORTL_BASE, true) == GPIO_INT_PIN_2)
    {
        enComandos cmd = cmdTminus;
        tx_queue_send(&config_queue, &cmd, TX_NO_WAIT);
        GPIOIntClear(GPIO_PORTL_BASE, GPIO_INT_PIN_2);
    }
}
