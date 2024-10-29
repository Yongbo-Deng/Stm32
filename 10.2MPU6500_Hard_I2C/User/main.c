#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6500.h"

int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	OLED_Init();
	
	MPU6500_Init();

	OLED_ShowString(1, 1, "ID:");
	OLED_ShowHexNum(1, 4, MPU6500_GetID(), 2);
	
	while (1){
		MPU6500_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
	}
}
