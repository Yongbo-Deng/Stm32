#include "stm32f10x.h" 
#include "MPU6500_Reg.h"

#define MPU6500_ADDRESS 0xD0        //Salve address

void MPU6500_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT) {     //While timeout break;
    uint16_t Timeout = 10000;
    while(I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS && Timeout != 0) {
        Timeout --;
    }
}

void MPU6500_WriteReg(uint8_t RegAddress, uint8_t Data) {
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6500_ADDRESS, I2C_Direction_Transmitter);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, RegAddress);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);

    I2C_SendData(I2C2, Data);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6500_ReadReg(uint8_t RegAddress) {
    uint8_t Data;
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6500_ADDRESS, I2C_Direction_Transmitter);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
    
    I2C_SendData(I2C2, RegAddress);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6500_ADDRESS, I2C_Direction_Receiver);
    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

    I2C_AcknowledgeConfig(I2C2, DISABLE);   //When recieving the last Byte, pre-disable (Ack = 1).
    I2C_GenerateSTOP(I2C2, ENABLE);         //And request for stop.

    MPU6500_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
    Data = I2C_ReceiveData(I2C2);   //Read DR.
    
    I2C_AcknowledgeConfig(I2C2, ENABLE);   //Restored to enable (Ack = 0).

    return Data;

}

void MPU6500_Init(void) {
    // MyI2C_Init();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

    I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_ClockSpeed = 50000;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2, &I2C_InitStruct);

    I2C_Cmd(I2C2, ENABLE);

    MPU6500_WriteReg(MPU6500_PWR_MGMT_1, 0x01);	//Wake up and gyroscope clock.
    MPU6500_WriteReg(MPU6500_PWR_MGMT_2, 0x00);
    MPU6500_WriteReg(MPU6500_SMPLRT_DIV, 0x09);
    MPU6500_WriteReg(MPU6500_CONFIG, 0x06);
    MPU6500_WriteReg(MPU6500_GYRO_CONFIG, 0x18);
    MPU6500_WriteReg(MPU6500_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6500_GetID(void) {
    return MPU6500_ReadReg(MPU6500_WHO_AM_I);
}

void MPU6500_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ) {
	*AccX = MPU6500_ReadReg(MPU6500_ACCEL_XOUT_H) << 8;     //High 8 digits.
	*AccX |= MPU6500_ReadReg(MPU6500_ACCEL_XOUT_L);         //Low 9 digits.
	
	*AccY = MPU6500_ReadReg(MPU6500_ACCEL_YOUT_H) << 8;
	*AccY |= MPU6500_ReadReg(MPU6500_ACCEL_YOUT_L);
	
	*AccZ = MPU6500_ReadReg(MPU6500_ACCEL_ZOUT_H) << 8;
	*AccZ |= MPU6500_ReadReg(MPU6500_ACCEL_ZOUT_L);
	
	*GyroX = MPU6500_ReadReg(MPU6500_GYRO_XOUT_H) << 8;
	*GyroX |= MPU6500_ReadReg(MPU6500_GYRO_XOUT_L);
	
	*GyroY = MPU6500_ReadReg(MPU6500_GYRO_YOUT_H) << 8;
	*GyroY = MPU6500_ReadReg(MPU6500_GYRO_YOUT_L);
	
	*GyroZ = MPU6500_ReadReg(MPU6500_GYRO_ZOUT_H) << 8;
	*GyroZ |= MPU6500_ReadReg(MPU6500_GYRO_ZOUT_L);
}
