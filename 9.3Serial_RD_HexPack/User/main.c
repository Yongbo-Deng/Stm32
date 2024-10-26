#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"

uint8_t KeyNum;

void Increase(void);

int main(void){
	Key_Init();	
	OLED_Init();
	OLED_ShowString(1, 1, "TxPacket:");
	OLED_ShowString(3, 1, "RxPacket:");
	Serial_Init();

	Serial_TxPacket[0] = 0x01;
	Serial_TxPacket[1] = 0x02;
	Serial_TxPacket[2] = 0x03;
	Serial_TxPacket[3] = 0x04;

	while (1){
		KeyNum = Key_GetNum();
		if (KeyNum == 1) {
			Serial_SendPacket();
			Increase();
		}

		if (Serial_GetRxFlag() == 1) {
			for (uint8_t i = 0; i < 4; i++) {
			OLED_ShowHexNum(4, (1 + (3 * i)), Serial_RxPacket[i], 2);
			}
		}
	}
}

void Increase(void) {
	for (uint8_t i = 0; i < 4; i++) {
		OLED_ShowHexNum(2, (1 + (3 * i)), Serial_TxPacket[i], 2);
		Serial_TxPacket[i] ++;
	}
}


