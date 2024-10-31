#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

void W25Q64_Init(void) {
    MySPI_Init();
}

void W25Q64_ReadId(uint8_t *MID, uint16_t *DID) {
    MySPI_Start();
    MySPI_SwapByte(W25Q64_JEDEC_ID);
    *MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE) << 8;
    *DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    MySPI_Stop();
}

void W25Q64_WriteEnable(void) {
    MySPI_Start();
    MySPI_SwapByte(W25Q64_WRITE_ENABLE);
    MySPI_Stop();
}

void W25Q64_WaitBusy(void) {
    int32_t Timeout = 10000;
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    while(((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01) && Timeout > 0) {Timeout --;};
    MySPI_Stop();
}

void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count) {
    W25Q64_WaitBusy();
    W25Q64_WriteEnable();   //Auto disable in the next Stop.
    MySPI_Start();
    MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for(uint16_t i = 0; i < Count; i ++) {
        MySPI_SwapByte(DataArray[i]);
    }
    MySPI_Stop();
}

void W25Q64_SectorErase(uint32_t Address) {
    W25Q64_WaitBusy();
    W25Q64_WriteEnable();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    MySPI_Stop();

}

void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count) {
    W25Q64_WaitBusy();
    MySPI_Start();
    MySPI_SwapByte(W25Q64_READ_DATA);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    while(Count) {
        *DataArray = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
        DataArray ++;
        Count --;
    }
    MySPI_Stop();
}


