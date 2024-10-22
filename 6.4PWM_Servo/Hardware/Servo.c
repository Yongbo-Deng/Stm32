#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Servo_Init(void) {
	PWM_Init();
}

void Servo_SetAngle(float Angle) {
	TIM_SetCompare2(TIM2, 500 + Angle / 180 * 2000);
}

