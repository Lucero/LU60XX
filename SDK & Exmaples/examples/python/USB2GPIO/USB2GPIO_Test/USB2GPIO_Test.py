#-*- coding: utf-8 -*-
from ctypes import *
import platform
from time import sleep
from usb_device import *
from usb2gpio import *

if __name__ == '__main__':
    DevHandles = (c_int * 20)()
    DevHandle = 0
    # Scan device
    ret = USB_ScanDevice(byref(DevHandles))
    if(ret == 0):
        print("No device connected!")
        exit()
    else:
        print("Have %d device connected!"%ret)
        DevHandle = DevHandles[0]#选择设备0
    # Open device
    ret = USB_OpenDevice(DevHandle)
    if(bool(ret)):
        print("Open device success!")
    else:
        print("Open device faild!")
        exit()
    # Get device infomation
    LuceroInfo = DEVICE_INFO()
    LuceroFunctionString = (c_char * 256)()
    ret = DEV_GetDeviceInfo(DevHandle,byref(LuceroInfo),byref(LuceroFunctionString))
    if(bool(ret)):
        print("Lucero device infomation:")
        print("--Firmware Name: %s"%bytes(LuceroInfo.FirmwareName).decode('ascii'))
        print("--Firmware Version: v%d.%d.%d"%((LuceroInfo.FirmwareVersion>>24)&0xFF,(LuceroInfo.FirmwareVersion>>16)&0xFF,LuceroInfo.FirmwareVersion&0xFFFF))
        print("--Hardware Version: v%d.%d.%d"%((LuceroInfo.HardwareVersion>>24)&0xFF,(LuceroInfo.HardwareVersion>>16)&0xFF,LuceroInfo.HardwareVersion&0xFFFF))
        print("--Build Date: %s"%bytes(LuceroInfo.BuildDate).decode('ascii'))
        print("--Serial Number: ",end=' ')
        for i in range(0, len(LuceroInfo.SerialNumber)):
            print("%08X"%LuceroInfo.SerialNumber[i],end='')
        print("")
        print("--Function String: %s"%bytes(LuceroFunctionString.value).decode('ascii'))
    else:
        print("Get device infomation faild!")
        exit()
    # 设置GPIO输入输出电压，只针对带可变电压输出版本的适配器有用，其他适配器默认是3.3V
    DEV_SetPowerLevel(DevHandle,POWER_LEVEL_3V3)
    # 输出测试没——上下拉
    GPIO_SetOutput(DevHandle,0xFFFF,0)
    for i in range(0,10):
        GPIO_Write(DevHandle,0xFFFF,0xAAAA)
        GPIO_Write(DevHandle,0xFFFF,0x5555)
    # 输出测试——上拉
    GPIO_SetOutput(DevHandle,0xFFFF,1)
    for i in range(0,10):
        GPIO_Write(DevHandle,0xFFFF,0xAAAA)
        GPIO_Write(DevHandle,0xFFFF,0x5555)
    # 输出测试——下拉
    GPIO_SetOutput(DevHandle,0xFFFF,2)
    for i in range(0,10):
        GPIO_Write(DevHandle,0xFFFF,0xAAAA)
        GPIO_Write(DevHandle,0xFFFF,0x5555)
    # 测试输入——浮空
    GPIO_SetInput(DevHandle,0xFFFF,0)
    PinValue = c_uint(0)
    GPIO_Read(DevHandle,0xFFFF,byref(PinValue))
    print("READ DATA(Float):%04X"%PinValue.value)
    # 测试输入——上拉输入
    GPIO_SetInput(DevHandle,0xFFFF,1)
    GPIO_Read(DevHandle,0xFFFF,byref(PinValue))
    print("READ DATA(Pu):%04X"%PinValue.value)
    # 测试输入——下拉输入
    GPIO_SetInput(DevHandle,0xFFFF,2)
    GPIO_Read(DevHandle,0xFFFF,byref(PinValue))
    print("READ DATA(Pd):%04X"%PinValue.value)
    # 测试开漏输入——浮空
    GPIO_SetOpenDrain(DevHandle,0xFFFF,0)
    GPIO_Read(DevHandle,0xFFFF,byref(PinValue))
    print("READ DATA(OD-Float):%04X"%PinValue.value)
    # 测试开漏输入——上拉输入
    GPIO_SetOpenDrain(DevHandle,0xFFFF,1)
    GPIO_Read(DevHandle,0xFFFF,byref(PinValue))
    print("READ DATA(OD-Pu):%04X"%PinValue.value)
    # 测试开漏输入——下拉输入
    GPIO_SetOpenDrain(DevHandle,0xFFFF,2)
    GPIO_Read(DevHandle,0xFFFF,byref(PinValue))
    print("READ DATA(OD-Pd):%04X"%PinValue.value)
    # Close device
    ret = USB_CloseDevice(DevHandle)
    if(bool(ret)):
        print("Close device success!")
    else:
        print("Close device faild!")
        exit()
