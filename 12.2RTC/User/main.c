#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"
#include <time.h>

uint16_t ArrayWrite[] = {0x01, 0x02, 0x03, 0x03};
uint16_t ArrayRead[2];

int main(void)
{
	OLED_Init();
	MyRTC_Init();
	
	OLED_ShowString(1, 1, "Date:yyyy-mm-dd");
	OLED_ShowString(2, 1, "Time:hh:mm:ss");		//Unknown BUG: One time, every 1.5 second, ss+1.
	OLED_ShowString(3, 1, "CNT :");
	OLED_ShowString(4, 1, "DIV :");

	

	while (1){
		MyRTC_ReadTime();
		OLED_ShowNum(1, 6, time_date.tm_year + 1900, 4);
		OLED_ShowNum(1, 11, time_date.tm_mon + 1, 2);
		OLED_ShowNum(1, 14, time_date.tm_mday, 2);
		OLED_ShowNum(2, 6, time_date.tm_hour, 2);
		OLED_ShowNum(2, 9, time_date.tm_min, 2);
		OLED_ShowNum(2, 12, time_date.tm_sec, 2);
		
		OLED_ShowNum(3, 6, RTC_GetCounter(), 10);
		OLED_ShowNum(4, 6, RTC_GetDivider(), 10);
	}
}
