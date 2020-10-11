#-*- coding: utf-8 -*-
from ctypes import *
import platform
from time import sleep
from usb_device import *
from usb2adc import *

# define callback function
def GetAdcDataHandle(DevIndex,pData,DataNum):
    print("Get ADC data number:%d"%DataNum)
    if(DataNum > 0):
        ADCData = (c_ushort * DataNum)()# 声明本地内存存储空间
        memmove(byref(ADCData),c_char_p(pData),DataNum*2)# 拷贝数据到本地，DataNum为ADC数量，每个ADC有2字节，所以得拷贝DataNum*2
        print("ADCData = %f V"%(ADCData[0]*3.3/4095))# print the voltage value
    return 0

if __name__ == '__main__': 
    DevIndex = 0
    ADCChannel = 0x01
    DevHandles = (c_uint * 20)()
    # Scan device
    ret = USB_ScanDevice(DevHandles)
    if(ret == 0):
        print("No device connected!")
        exit()
    else:
        print("Have %d device connected!"%ret)
    # Open device
    ret = USB_OpenDevice(DevHandles[DevIndex])
    if(bool(ret)):
        print("Open device success!")
    else:
        print("Open device faild!")
        exit()
    # Get device infomation
    LuceroInfo = DEVICE_INFO()
    LuceroFunctionString = (c_char * 256)()
    ret = DEV_GetDeviceInfo(DevHandles[DevIndex],byref(LuceroInfo),byref(LuceroFunctionString))
    if(bool(ret)):
        print("Lucero device infomation:")
        print("--Firmware Name: %s"%bytes(LuceroInfo.FirmwareName).decode('ascii'))
        print("--Firmware Version: v%d.%d.%d"%((LuceroInfo.FirmwareVersion>>24)&0xFF,(LuceroInfo.FirmwareVersion>>16)&0xFF,LuceroInfo.FirmwareVersion&0xFFFF))
        print("--Hardware Version: v%d.%d.%d"%((LuceroInfo.HardwareVersion>>24)&0xFF,(LuceroInfo.HardwareVersion>>16)&0xFF,LuceroInfo.HardwareVersion&0xFFFF))
        print("--Build Date: %s"%bytes(LuceroInfo.BuildDate).decode('ascii'))
        print("--Serial Number: ",end='')
        for i in range(0, len(LuceroInfo.SerialNumber)):
            print("%08X"%LuceroInfo.SerialNumber[i],end='')
        print("")
        print("--Function String: %s"%bytes(LuceroFunctionString.value).decode('ascii'))
    else:
        print("Get device infomation faild!")
        exit()
    # Initialize adc
    ret = ADC_Init(DevHandles[DevIndex],ADCChannel,1000000)
    if(ret != ADC_SUCCESS):
        print("Initialize adc faild!")
        exit()
    else:
        print("Initialize adc success")
    # Read adc value
    ADCData = (c_ushort * 8)()
    ret = ADC_Read(DevHandles[DevIndex],byref(ADCData),len(ADCData))
    if(ret != ADC_SUCCESS):
        print("Adc read data faild!")
        exit()
    else:
        print("Read Data:")
        for i in range(0,len(ADCData)):
            print("ADCData[%d] = %f V"%(i,ADCData[i]*3.3/4095))
    # Delay
    sleep(0.01)
    # Close device
    ret = USB_CloseDevice(DevHandles[DevIndex])
    if(bool(ret)):
        print("Close device success!")
    else:
        print("Close device faild!")
        exit()
