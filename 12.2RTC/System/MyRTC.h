#ifndef __MYRTC_H
#define __MYRTC_H

extern struct tm time_date;

void MyRTC_Init(void);
uint32_t MyRTC_GetCounter(void);
void MyRTC_SetTime(void);
void MyRTC_ReadTime(void);

#endif

