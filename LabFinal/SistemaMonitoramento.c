/*
* Sistema de Monitoramento
*/
#include "SistemaMonitoramento.h"
#include <stdio.h>

extern TX_QUEUE monitor_queue;

void monitoramentoThreadFxn(ULONG thread_input)
{

  ULONG temp = 0;
  while(1)
  {
    tx_thread_sleep(3000);
    uint32_t potValue;
    /* Habilita o ADC0*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    /* Aguarda passar o periodo de medicao */
    tx_thread_sleep(20);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)){}
    /* Realiza medicao */
    //
    // Enable the first sample sequencer to capture the value of channel 0 when
    // the processor trigger occurs.
    //
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0,

    ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);

    ADCSequenceEnable(ADC0_BASE, 0);
    //
    // Trigger the sample sequence.
    //
    ADCProcessorTrigger(ADC0_BASE, 0);
    //
    // Wait until the sample sequence has completed.
    //
    while(!ADCIntStatus(ADC0_BASE, 0, false))
    {
    }
    //
    // Read the value from the ADC.
    //
    ADCSequenceDataGet(ADC0_BASE, 0, &potValue);
    printf("%d\n", potValue);
    /* Envia dados para as tarefas interessadas */
    temp = (potValue*100/4096)*40/100 + 10;
    tx_queue_send(&monitor_queue, &temp, TX_NO_WAIT);
    
  }
}
