#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main(void)
{
	OLED_Init();

	Serial_Init();

	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};

	Serial_SendByte(0x41);
	Serial_SendArray(MyArray, 4);
	Serial_SendString("HelloWorld!\r\n");
	Serial_SendNumber(12345, 5);
	printf("Num=%d\r\n", 2024);

	Serial_Printf("Num=%d\r\n", 8964);
	while (1){
		
	}
}
