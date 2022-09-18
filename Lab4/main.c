/**
*       @file main.c
*       @brief Arquivo main do Lab04 da materia de Sistemas Embarcados
*       @author Paulo Sergio Avila Junior e Cassio Keisuke Yamauchi
*/

#include <stdint.h>
#include "lab04_comm.h"
#include "lab04_joystick.h"
#include "lab04_ledrgb.h"
#include "lab04_luminosidade.h"


static void setup_ADC()
{}

static void setup_I2C()
{}

static void setup_UART()
{}

static void setup_GPIO()
{}

volatile uint8_t medFlag = 0;
volatile uint8_t sendFlag = 0;
volatile uint32_t sendTimer = 0;

/* Timer de 50ms */
void vTIMER_callbackFxn()
{
  /* Flag para realizar as medicoes */
  medFlag = 1;
  
  /* Flag para enviar os dados */
  if(!sendTimer)
  {
    sendFlag = 1;
    /* A cada 4 interrupcoes, enviar dados */
    sendTimer = 4;
  }
}

static void setup_TIMER()
{}

int main()
{
  setup_ADC();
  setup_I2C();
  setup_UART();
  setup_GPIO();
  setup_TIMER();
  
  /* Loop infinito */
  while(1)
  {
    if(medFlag)
    {
      vJOY_Poll();
      vLUM_Poll();
    }
    
    if(sendFlag)
    {
      vRGB_Poll();
      vCOMM_Poll();
    }
  }
  
  return 0;
}
