#define GET_FIRMWARE_INFO

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LUCERO;

namespace LUCEROADCTest
{
    class Program
    {
        static UInt32 BitCount(UInt32 data)
        {
            UInt32 count = 0;
            while (data!=0x00)
            {
                count++;
                data &= (data - 1);
            }
            return count;
        }
        static void Main(string[] args)
        {
            usb_device.DEVICE_INFO DevInfo = new usb_device.DEVICE_INFO();
            Int32[] DevHandles = new Int32[20];
            Int32 DevHandle = 0;
            Byte ADC_Channel = 0x01;
            bool state;
            Int32 DevNum, ret;
            Int32 ADC_NUMS = 10;
            UInt16[] Buffer = new UInt16[40960];
            //扫描查找设备
            DevNum = usb_device.USB_ScanDevice(DevHandles);
            if (DevNum <= 0)
            {
                Console.WriteLine("No device connected!");
                Console.ReadLine();
                return;
            }
            else
            {
                Console.WriteLine("Have {0} device connected!", DevNum);
            }
            DevHandle = DevHandles[0];
            //打开设备
            state = usb_device.USB_OpenDevice(DevHandle);
            if (!state)
            {
                Console.WriteLine("Open device error!");
                Console.ReadLine();
                return;
            }
            else
            {
                Console.WriteLine("Open device success!");
            }
            //获取固件信息
#if GET_FIRMWARE_INFO
            StringBuilder FuncStr = new StringBuilder(256);
            state = usb_device.DEV_GetDeviceInfo(DevHandle, ref DevInfo, FuncStr);
            if (!state)
            {
                Console.WriteLine("Get device infomation error!");
                Console.ReadLine();
                return;
            }
            else
            {
                Console.WriteLine("Firmware Info:");
                Console.WriteLine("    Name:" + Encoding.Default.GetString(DevInfo.FirmwareName));
                Console.WriteLine("    Build Date:" + Encoding.Default.GetString(DevInfo.BuildDate));
                Console.WriteLine("    Firmware Version:v{0}.{1}.{2}", (DevInfo.FirmwareVersion >> 24) & 0xFF, (DevInfo.FirmwareVersion >> 16) & 0xFF, DevInfo.FirmwareVersion & 0xFFFF);
                Console.WriteLine("    Hardware Version:v{0}.{1}.{2}", (DevInfo.HardwareVersion >> 24) & 0xFF, (DevInfo.HardwareVersion >> 16) & 0xFF, DevInfo.HardwareVersion & 0xFFFF);
                Console.WriteLine("    Functions:" + DevInfo.Functions.ToString("X8"));
                Console.WriteLine("    Functions String:" + FuncStr);
            }
#endif
            //初始化设备
            ret = USB2ADC.ADC_Init(DevHandle, ADC_Channel, 1000000);
            if (ret != USB2ADC.ADC_SUCCESS)
            {
                Console.WriteLine("Init adc error!");
                Console.ReadLine();
                return;
            }
            //读取ADC数据
            ret = USB2ADC.ADC_Read(DevHandle, Buffer, ADC_NUMS);
            if (ret != USB2ADC.ADC_SUCCESS)
            {
                Console.WriteLine("Read adc error!\n");
                Console.ReadLine();
                return;
            }
            else
            {
                for (int i = 0; i < ADC_NUMS * BitCount(ADC_Channel); i++)
                {
                    Console.WriteLine("ADC Data[%d] = %fV\n", i, (Buffer[i] * 3.3) / 4095);
                }
            }
            //关闭设备
            usb_device.USB_CloseDevice(DevHandle);
        }
    }
}
