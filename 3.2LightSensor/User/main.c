#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

int main(void)
{
	Buzzer_Init();
	LightSensor_Init();
	uint8_t status;
	while(1) {
		status = LightSensor_Get();
		if (status == 1) {
			Buzzer_ON();
			Delay_ms(100);
		} else {
			Buzzer_OFF();
			Delay_ms(100);
		}
	}
}
