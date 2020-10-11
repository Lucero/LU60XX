#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "usb_device.h"
#include "usb2adc.h"

#define CONTINUE_GET_ADC_DATA   1
#define ADC_NUMS                10
//计算一个整数bit位为1的个数
uint32_t BitCount(uint32_t data)
{
  uint32_t count=0;
  while(data){
    count++;
    data&=(data-1);
  }
  return count;
}
int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    int DevHandle[10];
    bool state;
    int ret;
    char ADC_Channel = 0x03;//使能ADC_CH0和ADC_CH1
    short Buffer[40960];
    //扫描查找设备
    ret = USB_ScanDevice(DevHandle);
    if(ret <= 0){
        printf("No device connected!\n");
        return 0;
    }
    //打开设备
    state = USB_OpenDevice(DevHandle[0]);
    if(!state){
        printf("Open device error!\n");
        return 0;
    }
    //获取固件信息
    char FuncStr[256]={0};
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,FuncStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
        printf("Firmware Info:\n");
        printf("    Name:%s\n",DevInfo.FirmwareName);
        printf("    Build Date:%s\n",DevInfo.BuildDate);
        printf("    Firmware Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("    Hardware Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
        printf("    Functions:%08X\n",DevInfo.Functions);
        printf("    Functions:%s\n",FuncStr);
    }
    //初始化ADC
    ret = ADC_Init(DevHandle[0],ADC_Channel,1000000);
    if(ret != ADC_SUCCESS){
        printf("Init adc error!\n");
        return 0;
    }
    //手动读取ADC数据
    ret = ADC_Read(DevHandle[0],Buffer,ADC_NUMS);
    if(ret != ADC_SUCCESS){
        printf("Read adc error!\n");
        return 0;
    }else{
        for(int i=0;i<ADC_NUMS*BitCount(ADC_Channel);i++){
            printf("ADC Data[%d] = %fV\n",i,(Buffer[i]*3.3)/4095);
        }
    }
    //手动读取ADC数据
    ret = ADC_Read(DevHandle[0],Buffer,ADC_NUMS);
    if(ret != ADC_SUCCESS){
        printf("Read adc error!\n");
        return 0;
    }else{
        for(int i=0;i<ADC_NUMS*BitCount(ADC_Channel);i++){
            printf("ADC Data[%d] = %fV\n",i,(Buffer[i]*3.3)/4095);
        }
    }
    //关闭设备
    USB_CloseDevice(DevHandle[0]);
    return 0;
}

