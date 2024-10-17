#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

int main(void)
{
	uint8_t key;
	LED_Init();
	Key_Init();
	while (1)
	{
		key = Key_getNum();
		if (key != 0) {
			Turn(key);
		}
	}
}
