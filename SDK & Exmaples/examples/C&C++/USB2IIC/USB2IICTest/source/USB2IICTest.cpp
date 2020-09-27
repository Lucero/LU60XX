#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "usb_device.h"
#include "usb2iic.h"
#include "windows.h"

int main(int argc, const char* argv[])
{
	int ret = 0;
	int IICIndex = 0;
	bool res = false;
	int32_t DevHandle[32] = { 0 };
	DEVICE_INFO DevInfo;
	char buf[512] = { 0 };
	uint32_t speed = 0;

	if (USB_ScanDevice(DevHandle) <= 0) {
		printf("Operation failed!\n");
		return -1;
	}
	if (USB_OpenDevice(DevHandle[0]) == false) {
		printf("Operation failed!\n");
		return -1;
	}
	res = DEV_GetDeviceInfo(DevHandle[0], &DevInfo, buf);
	if (!res) {
		printf("Get device infomation error!\n");
		return -1;
	}
	else {
		printf("Firmware Info:\n");
		printf("    Name:\t\t%s\n", DevInfo.FirmwareName);
		printf("    Build Date:\t\t%s\n", DevInfo.BuildDate);
		printf("    Firmware Version:\tv%d.%d.%d\n", (DevInfo.FirmwareVersion >> 24) & 0xFF, (DevInfo.FirmwareVersion >> 16) & 0xFF, DevInfo.FirmwareVersion & 0xFFFF);
		printf("    Hardware Version:\tv%d.%d.%d\n", (DevInfo.HardwareVersion >> 24) & 0xFF, (DevInfo.HardwareVersion >> 16) & 0xFF, DevInfo.HardwareVersion & 0xFFFF);
		printf("    Functions Code:\t%08X\n", DevInfo.Functions);
		printf("    Functions:\t\t%s\n", buf);
	}

	IIC_CONFIG IIC_Config;
	IIC_Config.EnablePu = 1;
	IIC_Config.AddrBits = 7;
	IIC_Config.ClockSpeedHz = 100000;
	IIC_Config.Master = 1;

	ret = IIC_Init(DevHandle[0], IICIndex, &IIC_Config);
	if (ret != IIC_SUCCESS) {
		printf("Config IIC failed!\n");
		return 0;
	}
	else {
		printf("Config IIC IIC_SUCCESS!\n");
	}

	//获取总线上能应答的从机地址
	short SlaveAddrs[128];  //地址存储缓冲区
	int SlaveAddrNum = 0;   //返回应答的地址个数
	SlaveAddrNum = IIC_GetSlaveAddr(DevHandle[0], IICIndex, SlaveAddrs);
	if (SlaveAddrNum > 0) {
		printf("Get %d slave address!\n", SlaveAddrNum);
		for (int i = 0; i < SlaveAddrNum; i++) {
			printf("%02X ", SlaveAddrs[i]);
		}
		printf("\n");
	}
	else if (SlaveAddrNum == 0) {
		printf("Get %d slave address!\n", SlaveAddrNum);
		return 0;
	}
	else {
		printf("Get slave address error!\n");
		return 0;
	}

	//IIC 写数据
	unsigned char WriteBuffer[8] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };
	ret = IIC_WriteBytes(DevHandle[0], IICIndex, 0x50, WriteBuffer, sizeof(WriteBuffer), 1000);
	if (ret != IIC_SUCCESS) {
		printf("Write IIC failed!\n");
		printf("Error Code:%d\n", ret);
		return 0;
	}
	else {
		printf("Write IIC IIC_SUCCESS!\n");
	}

	//延时
#ifndef OS_UNIX
	Sleep(10);
#else
	usleep(10 * 1000);
#endif

	//IIC 读数据
	unsigned char ReadBuffer[8];
	ret = IIC_ReadBytes(DevHandle[0], IICIndex, 0x50, ReadBuffer, sizeof(ReadBuffer), 1000);
	if (ret != IIC_SUCCESS) {
		printf("Read IIC failed!\n");
		printf("Error Code:%d\n", ret);
		return 0;
	}
	else {
		printf("Read IIC IIC_SUCCESS!\n");
		printf("Read Data:\n");
		for (int i = 0; i < sizeof(ReadBuffer); i++) {
			printf("%02X ", ReadBuffer[i]);
		}
		printf("\n");
	}

	//延时
#ifndef OS_UNIX
	Sleep(10);
#else
	usleep(10 * 1000);
#endif

	//IIC 写读数据。也就是先发送数据，然后再次产生START信号，再读数据
	//注意：对于每个I2C设备，必须按照设备要求正确读写，否则可能会导致设备工作不正常，从而导致无法读写数据
	WriteBuffer[0] = 0x03;
	ret = IIC_WriteReadBytes(DevHandle[0], IICIndex, 0x50, WriteBuffer, 1, ReadBuffer, sizeof(ReadBuffer), 1000);
	if (ret != IIC_SUCCESS) {
		printf("WriteRead IIC failed!\n");
		printf("Error Code:%d\n", ret);
		return 0;
	}
	else {
		printf("WriteRead IIC IIC_SUCCESS!\n");
		printf("Read Data:\n");
		for (int i = 0; i < sizeof(ReadBuffer); i++) {
			printf("%02X ", ReadBuffer[i]);
		}
		printf("\n");
	}

	//getchar();
	//关闭设备
	USB_CloseDevice(DevHandle[0]);
	return 0;
}

