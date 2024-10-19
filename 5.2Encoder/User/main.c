#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Encoder.h"
#include <stdlib.h>
int main(void)
{
	Encoder_Init();
	LED_Init();
	int16_t Num = 0;
	//OLED_Init();
	//OLED_ShowString(1, 1, "Count:");
	while (1)
	{
		//OLED_ShowNum(1, 7, CountSensor_Get(), 5);
		Num ++; 
		LED_Print(abs(Encoder_Get()) % 6);
		Delay_ms(300);
		
	}
}
