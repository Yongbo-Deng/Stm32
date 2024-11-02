#include "stm32f10x.h"                  // Device header

void LED_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructureA;
	GPIO_InitStructureA.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructureA.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructureA.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructureA);
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
}

static uint16_t getPin(uint8_t n) {
	uint16_t pin[8] = {GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4
	,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7};
	return pin[n];
}

void LED_ON(uint8_t n) {
	uint16_t pin = getPin(n);
	GPIO_ResetBits(GPIOA, pin);
}

void LED_OFF(uint8_t n) {
	uint16_t pin = getPin(n);
	GPIO_SetBits(GPIOA, pin);
}

void LED_Turn(uint8_t n) {
	uint16_t pin = getPin(n);
	uint8_t status = GPIO_ReadOutputDataBit(GPIOA, pin);
	GPIO_WriteBit(GPIOA, pin, (BitAction) (1-status));
}

