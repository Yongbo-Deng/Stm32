#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];
static uint8_t Serial_RxFlag = 0;


void Serial_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

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

int fputc(int ch, FILE *f) {    //Override printf function.
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

uint8_t Serial_GetRxFlag(void) {
    if (Serial_RxFlag == 1) {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

void USART1_IRQHandler(void) {
    static uint8_t RxState = 0;
    static uint8_t pRxPacket = 0;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        uint8_t RxData = USART_ReceiveData(USART1);
        switch (RxState) {
        case 0: //Waiting for head sign.
            if (RxData == 0xFF) {
                RxState = 1;
                pRxPacket = 0;
            }
            break;
        case 1: //Reciving data.
            Serial_RxPacket[pRxPacket] = RxData;
            pRxPacket ++;
            if (pRxPacket >= 4) {
                RxState = 2;
            }
            break;
        case 2: //Waiting for tail sign.
            if (RxData == 0xFE) {
                RxState = 0;
                Serial_RxFlag = 1;
            }
            break;
        default:
            break;
        }
    }

}

void Serial_SendPacket(void) {
    Serial_SendByte(0xFF);
    Serial_SendArray(Serial_TxPacket, 4);
    Serial_SendByte(0xFE);
}
