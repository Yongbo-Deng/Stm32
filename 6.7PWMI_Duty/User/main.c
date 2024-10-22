#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

uint32_t Freq;
uint32_t Duty;

int main(void)
{
	OLED_Init();
	PWM_Init();
	IC_Init();
	
	PWM_SetPrescaler(720 -1);		//Freqy = 1kHz
	PWM_SetCompare1(59);			//Duty = 50%
	OLED_ShowString(1, 1, "Freq:00000Hz");
	OLED_ShowString(1, 1, "Duty:00%");
	
	
	while (1)
	{
		Freq = IC_GetFreq();
		Duty = IC_GetDuty();
		OLED_ShowNum(1, 6, Freq, 5);
		OLED_ShowNum(2, 6, Duty, 2);
	}
}




