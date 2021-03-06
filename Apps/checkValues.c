#include "checkValues.h"
#include "KS0108/KS0108.h"
#include "stdio.h"
#include "DMA/adc.h"

void vCheckTask(void *pvParameters) {
	while (1) {
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
		int i;
		for (i = 0; i < ADC_Channels; i++) {
			if (ADC.milivolt[i] > ADC.mvMaxTreshold[i]) {
				ADC.overTreshold[i] = 1;
			} else if (ADC.milivolt[i] < ADC.mvMinTreshold[i]) {
				ADC.overTreshold[i] = 1;
			} else {
				ADC.overTreshold[i] = 0;
			}
		}
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		portTickType xLastWakeTime;
		const portTickType xTimeIncrement_ms = 500;
		xLastWakeTime = xTaskGetTickCount();
		vTaskDelayUntil(&xLastWakeTime, xTimeIncrement_ms);
	}
}
