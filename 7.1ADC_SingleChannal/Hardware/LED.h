#ifndef __LED_H
#define __LED_H

void LED_Init(void); 
void ON(uint8_t n);
void OFF(uint8_t n);
void Turn(uint8_t n);
uint16_t getPin(uint8_t n);

#endif
