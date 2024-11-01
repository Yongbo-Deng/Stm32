#include "stm32f10x.h"
#include <time.h>

void MyRTC_SetTime(void);

struct tm time_date;

void MyRTC_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);

    if(BKP_ReadBackupRegister(BKP_DR1) == 0) {
        RCC_LSEConfig(RCC_LSE_ON);
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);

        RTC_WaitForSynchro();
        RTC_WaitForLastTask();

        RTC_SetPrescaler(32768 -1);     //Encapsule ConfigMode().
        RTC_WaitForLastTask();

        RTC_SetCounter(1704096000);     //Initial Unix timestamp.
        RTC_WaitForLastTask();
        
        RTC_ExitConfigMode();
        RTC_WaitForLastTask();

        time_date.tm_year = 124;
        time_date.tm_mon = 0;
        time_date.tm_mday = 1;
        time_date.tm_hour = 23;
        time_date.tm_min = 58;
        time_date.tm_sec = 59;
        MyRTC_SetTime();
        BKP_WriteBackupRegister(BKP_DR1, 0xFFFF);
    } else {
        RTC_ExitConfigMode();
        RTC_WaitForLastTask();
    }
    
}

uint32_t MyRTC_GetCounter(void) {
    return RTC_GetCounter();
}

void MyRTC_SetTime(void) {
    int8_t timezone = -7;
    time_t time_cnt;
    time_cnt = mktime(&time_date);
    time_cnt -= 3600 * (timezone);
    RTC_SetCounter(time_cnt);
    RTC_WaitForLastTask();
}

void MyRTC_ReadTime(void) {
    int8_t timezone = -7;
    time_t time_cnt = RTC_GetCounter() + 3600 * (timezone);

    time_date = *localtime(&time_cnt);
}

