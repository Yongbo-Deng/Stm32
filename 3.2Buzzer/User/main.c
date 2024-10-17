#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"

int main(void)
{
	Buzzer_Init();
	while(1) {
		Buzzer_ON();
		Delay_ms(100);
		Buzzer_OFF();
		Delay_ms(100);
	}
}
