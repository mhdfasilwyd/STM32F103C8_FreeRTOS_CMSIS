#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define STACK_SIZE 32
#define PRIORITY 1

void Led_Init(void);
void vTaskLedOn (void *argument);
void vTaskLedOff (void *argument);

int main(void){
	
	Led_Init();
	
	xTaskCreate(vTaskLedOn, "LED_ON", STACK_SIZE, NULL, PRIORITY, NULL);
	xTaskCreate(vTaskLedOff, "LED_OFF", STACK_SIZE, NULL, PRIORITY, NULL);
	
	vTaskStartScheduler();
}

void Led_Init(void){
	
	GPIO_InitTypeDef led;
	led.GPIO_Pin = GPIO_Pin_13;
	led.GPIO_Mode = GPIO_Mode_Out_PP;
	led.GPIO_Speed = GPIO_Speed_2MHz;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_Init(GPIOC, &led);
}

void vTaskLedOn (void *argument){
	
	while(1)
	{
		vTaskDelay(1000);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		vTaskDelay(2000);
	}
	
}

void vTaskLedOff (void *argument){
	
	while(1)
	{
		vTaskDelay(2000);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		vTaskDelay(1000);
	}
	
}
