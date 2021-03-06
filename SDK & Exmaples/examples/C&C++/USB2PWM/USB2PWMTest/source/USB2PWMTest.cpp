#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "usb_device.h"
#include "usb2pwm.h"

int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    int DevHandle[10];
    bool state;
    int ret;
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
		printf("    Name:\t\t%s\n", DevInfo.FirmwareName);
		printf("    Build Date:\t\t%s\n", DevInfo.BuildDate);
		printf("    Firmware Version:\tv%d.%d.%d\n", (DevInfo.FirmwareVersion >> 24) & 0xFF, (DevInfo.FirmwareVersion >> 16) & 0xFF, DevInfo.FirmwareVersion & 0xFFFF);
		printf("    Hardware Version:\tv%d.%d.%d\n", (DevInfo.HardwareVersion >> 24) & 0xFF, (DevInfo.HardwareVersion >> 16) & 0xFF, DevInfo.HardwareVersion & 0xFFFF);
		printf("    Functions Code:\t%08X\n", DevInfo.Functions);
		printf("    Functions:\t\t%s\n", FuncStr);
    }
	
    //配置PWM相关参数并初始化PWM
    PWM_CONFIG PWMConfig;
    PWMConfig.ChannelMask = 0xFF;//初始化所有通道
    for (int i = 0; i < 8; i++) {
        PWMConfig.Polarity[i] = 1;//将所有PWM通道都设置为正极性
    }
    for (int i = 0; i < 8; i++) {
        PWMConfig.Precision[i] = 100;//将所有通道的占空比调节精度都设置为1%
    }
    for (int i = 0; i < 8; i++) {
        PWMConfig.Prescaler[i] = 10;//将所有通道的预分频器都设置为10。 PWM输出频率为200MHz/(PWMConfig.Precision*PWMConfig.Prescaler)
    }
    for (int i = 0; i < 8; i++) {
        PWMConfig.Pulse[i] = PWMConfig.Precision[i] * 20 / 100;//将所有通道的占空比都设置为20%
    }
    for (int i = 0; i < 8; i++) {
        PWMConfig.Phase[i] = 0;//波形相位，取值0到Precision-1
    }
    //初始化PWM
    ret = PWM_Init(DevHandle[0], &PWMConfig);
    if (ret != PWM_SUCCESS) {
        printf("Initialize pwm faild!\n");
        return ret;
    }
    else {
        printf("Initialize pwm sunccess!\n");
    }

    //启动PWM,RunTimeOfUs之后自动停止，利用该特性可以控制输出脉冲个数，脉冲个数=RunTimeOfUs*200/(PWMConfig.Precision*PWMConfig.Prescaler)
    unsigned int RunTimeOfUs = 0;
    ret = PWM_Start(DevHandle[0], PWMConfig.ChannelMask, RunTimeOfUs);
    if (ret != PWM_SUCCESS) {
        printf("Start pwm faild!\n");
        return ret;
    }
    else {
        printf("Start pwm sunccess!\n");
    }

    //改变PWM波形占空比
    uint16_t Plse[8];
    for(int i=0;i<100;i+=5){
        for(int j=0;j<8;j++){
            Plse[j] = i;
        }
        ret = PWM_SetPulse(DevHandle[0],PWMConfig.ChannelMask,Plse);
        if(ret != PWM_SUCCESS){
            printf("Start pwm faild!\n");
            return ret;
        }
    }
    printf("Set pulse success!\n");

    //停止PWM
    ret = PWM_Stop(DevHandle[0],PWMConfig.ChannelMask);
    if(ret != PWM_SUCCESS){
        printf("Stop pwm faild!\n");
        return ret;
    }else{
        printf("Stop pwm sunccess!\n");
    }
	
    //关闭设备
    USB_CloseDevice(DevHandle[0]);
	return 0;
}

