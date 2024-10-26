#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

void Serial_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);

    USART_Cmd(USART1, ENABLE);

}

void Serial_SendByte(uint8_t Byte) {
    USART_SendData(USART1, Byte);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array, uint16_t Length) {
    for(uint16_t i = 0; i < Length; i++) {
        Serial_SendByte(Array[i]);
    }

    /* while(Length) {
        USART_SendData(USART1, *Array);
        Array ++;
        Length --;
    } */
}

void Serial_SendString(char *String) {
    for(uint8_t i = 0; String[i] != '\0'; i ++) {
        Serial_SendByte(String[i]);
    }
}

void Serial_SendNumber(uint32_t Number, uint8_t Length) {
    for(uint8_t i = Length; i > 0; i --) {
        Serial_SendByte(Number / (10 ^ (i - 1)) % 10 + '0');    //First number in ASCII is '0'
    }
}

int fputc(int ch, FILE *f) {
    Serial_SendByte(ch);
    return ch;
}

void Serial_Printf(char *format, ...) {
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

