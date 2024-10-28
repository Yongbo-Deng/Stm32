#include "stm32f10x.h" 
#include "MyI2C.h"
#include "MPU6500_Reg.h"

#define MPU6500_ADDRESS 0xD0        //Salve address

void MPU6500_WriteReg(uint8_t RegAddress, uint8_t Data) {
    MyI2C_Start();
    MyI2C_SendByte(MPU6500_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck(); 
    MyI2C_SendByte(Data);
    MyI2C_ReceiveAck();
    MyI2C_Stop();
}

uint8_t MPU6500_ReadReg(uint8_t RegAddress) {
    uint8_t Data;
    MyI2C_Start();
    MyI2C_SendByte(MPU6500_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6500_ADDRESS | 0x01);
    MyI2C_ReceiveAck();
    Data = MyI2C_ReceiveByte();
    MyI2C_SendAck(1);
    MyI2C_Stop();

    return Data;
}

void MPU6500_Init(void) {
    MyI2C_Init();
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
