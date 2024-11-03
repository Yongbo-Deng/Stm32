#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"

uint8_t KeyNum;

int main(void) {
	OLED_Init();

	OLED_ShowString(1, 1, "IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET) {
		OLED_ShowString(2, 1, "IWDG Rest");
		Delay_ms(500);
		OLED_ShowString(2, 1, "          ");
		RCC_ClearFlag();
	} else {
		OLED_ShowString(2, 1, "RST");
		Delay_ms(500);
		OLED_ShowString(2, 1, "    ");
	}

	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(2);
	IWDG_SetReload(2500 -1);	//1000ms
	IWDG_ReloadCounter();
	IWDG_Enable();		//Auto read only.

	

	while (1){
		KeyNum = Key_GetNum();

		IWDG_ReloadCounter();
		OLED_ShowString(4, 1, "FEED");
		Delay_ms(600);	//My chip boundary about 900ms.
		OLED_ShowString(4, 1, "    ");
		Delay_ms(200);
	}
}
