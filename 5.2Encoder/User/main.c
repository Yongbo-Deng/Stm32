#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"

int main(void)
{
	Encoder_Init();
	int16_t Num = 0;
	OLED_Init();
	OLED_ShowString(1, 1, "Count:");
	
	while (1)
	{
		Num += Encoder_Get();
		OLED_ShowSignedNum(1, 7, Num, 5);	
	}
}
