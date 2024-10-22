#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num = 0;
uint16_t Hour = 0;
uint16_t Minute = 0;
uint16_t Second = 0;

void ShowClock(uint16_t Num);

int main(void)
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(4, 1, "00:00:00");
	OLED_ShowString(1, 1, "Num:");
	while (1)
	{
	}
}

void TIM2_IRQHandler() {
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) {
		Num ++;
		Second++;
		ShowClock(Second);
		OLED_ShowNum(1, 5, Num, 5);
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
	}
}

void ShowClock(uint16_t Num) {
	if(Second == 60) {
		Second = 0;
		Minute ++;
		if (Minute == 60) {
			Minute =0;
			Hour ++;
			if (Hour == 24) {
				Hour = 0;
			}
			OLED_ShowNum(4, 1, Hour, 2);
		}
		OLED_ShowNum(4, 4, Minute, 2);
	}
	OLED_ShowNum(4, 7, Second, 2);
}

