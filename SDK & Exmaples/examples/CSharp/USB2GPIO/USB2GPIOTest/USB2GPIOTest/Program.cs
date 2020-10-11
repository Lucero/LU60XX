using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LUCERO;

namespace USB2GPIOTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Int32[] DevHandles = new Int32[20];
            UInt32 PinValue = 0;

            Console.WriteLine("扫描设备...");
            int DevCnt = usb_device.USB_ScanDevice(DevHandles);//获取设备连接数，同时获取每个设备的序号
            if (DevCnt <= 0)
            {
                Console.WriteLine("获取设备列表失败！当前可能无设备连接！");
                return;
            }
            
            Console.Write("扫描到{0}个设备,每个设备的序号分别为：", DevCnt);
            for (int i = 0; i < DevCnt; i++)
            {
                Console.Write(DevHandles[i].ToString("X8") + "  ");
            }

            Console.WriteLine("\n打开第一个设备");
            bool state = usb_device.USB_OpenDevice(DevHandles[0]);
            if (!state)
            {
                Console.WriteLine("Open device error!" + DevHandles[0].ToString("X8"));
            }
            //设置GPIO电平（需要适配器支持）
            usb_device.DEV_SetPowerLevel(DevHandles[0], usb_device.POWER_LEVEL_3V3);
            //输出测试——没上下拉
            USB2GPIO.GPIO_SetOutput(DevHandles[0], 0xFFFF, 0);
            for (int i = 0; i < 10; i++)
            {
                USB2GPIO.GPIO_Write(DevHandles[0], 0xFFFF, 0xAAAA);
                USB2GPIO.GPIO_Write(DevHandles[0], 0xFFFF, 0x5555);
            }
            //输出测试——上拉
            USB2GPIO.GPIO_SetOutput(DevHandles[0], 0xFFFF, 1);
            for (int i = 0; i < 10; i++)
            {
                USB2GPIO.GPIO_Write(DevHandles[0], 0xFFFF, 0xAAAA);
                USB2GPIO.GPIO_Write(DevHandles[0], 0xFFFF, 0x5555);
            }
            //输出测试——下拉
            USB2GPIO.GPIO_SetOutput(DevHandles[0], 0xFFFF, 2);
            for (int i = 0; i < 10; i++)
            {
                USB2GPIO.GPIO_Write(DevHandles[0], 0xFFFF, 0xAAAA);
                USB2GPIO.GPIO_Write(DevHandles[0], 0xFFFF, 0x5555);
            }
            //测试输入——浮空
            USB2GPIO.GPIO_SetInput(DevHandles[0], 0xFFFF, 0);
            USB2GPIO.GPIO_Read(DevHandles[0], 0xFFFF, ref PinValue);
            Console.WriteLine("READ DATA(Float): " + PinValue.ToString("X4"));
            //测试输入——上拉输入
            USB2GPIO.GPIO_SetInput(DevHandles[0], 0xFFFF, 1);
            USB2GPIO.GPIO_Read(DevHandles[0], 0xFFFF, ref PinValue);
            Console.WriteLine("READ DATA(Pu): " + PinValue.ToString("X4"));
            //测试输入——下拉输入
            USB2GPIO.GPIO_SetInput(DevHandles[0], 0xFFFF, 2);
            USB2GPIO.GPIO_Read(DevHandles[0], 0xFFFF, ref PinValue);
            Console.WriteLine("READ DATA(Pd): " + PinValue.ToString("X4"));
            //测试开漏输入——浮空
            USB2GPIO.GPIO_SetOpenDrain(DevHandles[0], 0xFFFF, 0);
            USB2GPIO.GPIO_Read(DevHandles[0], 0xFFFF, ref PinValue);
            Console.WriteLine("READ DATA(OD-Float): " + PinValue.ToString("X4"));
            //测试开漏输入——上拉输入
            USB2GPIO.GPIO_SetOpenDrain(DevHandles[0], 0xFFFF, 1);
            USB2GPIO.GPIO_Read(DevHandles[0], 0xFFFF, ref PinValue);
            Console.WriteLine("READ DATA(OD-Pu): " + PinValue.ToString("X4"));
            //测试开漏输入——下拉输入
            USB2GPIO.GPIO_SetOpenDrain(DevHandles[0], 0xFFFF, 2);
            USB2GPIO.GPIO_Read(DevHandles[0], 0xFFFF, ref PinValue);
            Console.WriteLine("READ DATA(OD-Pd): " + PinValue.ToString("X4"));
            //关闭设备
            usb_device.USB_CloseDevice(DevHandles[0]);
        }
    }
}
