#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t KeyNum;

int main(void) {
	OLED_Init();

	OLED_ShowString(1, 1, "IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET) {
		//Reset by WWDG.
		OLED_ShowString(2, 1, "WWDG Rest");
		Delay_ms(500);
		OLED_ShowString(2, 1, "          ");
		RCC_ClearFlag();
	} else {
		//Reset by others.
		OLED_ShowString(2, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "    ");
	}

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

	WWDG_SetPrescaler(WWDG_Prescaler_8);	//27.77us
	WWDG_SetWindowValue(0x40 | 21);			//30ms
	WWDG_Enable(0x40 | 54);					//54 * 27.77 * 4098 = 50ms 
	Delay_ms(31);


	while (1){
		KeyNum = Key_GetNum();

		WWDG_SetCounter(0x40 | 54);
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(20);	//My chip boundary about 900ms.
		OLED_ShowString(4, 1, "    ");
		Delay_ms(20);
		
	}
}
