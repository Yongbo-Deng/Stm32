#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"
#include "Timer.h"

int16_t Speed;

int main(void)
{
	OLED_Init();
//	Timer_Init();
	Encoder_Init();
	OLED_ShowString(1, 1, "Speed:");
	while (1)
	{
		OLED_ShowSignedNum(1, 5, Speed, 5);
	}
}

void TIM2_IRQHandler() {
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		Speed = Encoder_GetSpeed();
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
	}
}

