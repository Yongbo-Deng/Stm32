#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

float Voltage;
uint16_t ADValue;

int main(void) {
	OLED_Init();
	AD_Init();
	
	OLED_ShowString(1, 1, "Vi:0.0");
	OLED_ShowString(2, 1, "AD:");
	while (1){
		ADValue = AD_GetValue();
		Voltage = (float) ADValue / 4095 * 3.3;
		OLED_ShowNum(1, 4, Voltage, 1);								//Integer
		OLED_ShowNum(1, 6, (uint16_t) (Voltage * 100) % 100, 2);	//Decimal
		OLED_ShowNum(2, 4, ADValue, 4);

	}
}
