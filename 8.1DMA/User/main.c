#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyDMA.h"

uint8_t DataA[4] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[4];


int main(void)
{
	OLED_Init();

	MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);

	OLED_ShowString(1, 1, "DataA");
	OLED_ShowString(3, 1, "DataB");
	OLED_ShowHexNum(1, 8, (uint32_t)DataA, 8);
	OLED_ShowHexNum(3, 8, (uint32_t)DataB, 8);

	while (1){
		DataA[0] ++;
		DataA[1] ++;
		DataA[2] ++;
		DataA[3] ++;

		for(uint8_t i = 0; i < 4; i++) {
		OLED_ShowHexNum(2, 1 + 3 * i, DataA[i], 2);
		OLED_ShowHexNum(4, 1 + 3 * i, DataB[i], 2);
		}

		Delay_ms(1000);

		MyDMA_Transfer();

		for(uint8_t i = 0; i < 4; i++) {
		OLED_ShowHexNum(2, 1 + 3 * i, DataA[i], 2);
		OLED_ShowHexNum(4, 1 + 3 * i, DataB[i], 2);
		}

		Delay_ms(1000);
	}
}
 