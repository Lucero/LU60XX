using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using LUCERO;

namespace USB2PWMTest
{
    class Program
    {
        static void Main(string[] args)
        {
            usb_device.DEVICE_INFO DevInfo = new usb_device.DEVICE_INFO();
            USB2PWM.PWM_CONFIG PWMConfig = new USB2PWM.PWM_CONFIG();
            Int32[] DevHandles = new Int32[20];
            Int32 DevHandle = 0;
            bool state;
            Int32 DevNum, ret;
            Byte[] WriteBuffer = new Byte[64];
            Byte[] ReadBuffer = new Byte[20480];
            //扫描查找设备
            DevNum = usb_device.USB_ScanDevice(DevHandles);
            if (DevNum <= 0)
            {
                Console.WriteLine("No device connected!");
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
                return;
            }
            else
            {
                Console.WriteLine("Open device success!");
            }
            //获取固件信息
            StringBuilder FuncStr = new StringBuilder(256);
            state = usb_device.DEV_GetDeviceInfo(DevHandle, ref DevInfo, FuncStr);
            if (!state)
            {
                Console.WriteLine("Get device infomation error!");
                return;
            }
            else
            {
                Console.WriteLine("Firmware Info:");
                Console.WriteLine("    Name:\t\t" + Encoding.Default.GetString(DevInfo.FirmwareName));
                Console.WriteLine("    Build Date:\t\t" + Encoding.Default.GetString(DevInfo.BuildDate));
                Console.WriteLine("    Firmware Version:\tv{0}.{1}.{2}", (DevInfo.FirmwareVersion >> 24) & 0xFF, (DevInfo.FirmwareVersion >> 16) & 0xFF, DevInfo.FirmwareVersion & 0xFFFF);
                Console.WriteLine("    Hardware Version:\tv{0}.{1}.{2}", (DevInfo.HardwareVersion >> 24) & 0xFF, (DevInfo.HardwareVersion >> 16) & 0xFF, DevInfo.HardwareVersion & 0xFFFF);
                Console.WriteLine("    Functions:\t\t" + DevInfo.Functions.ToString("X8"));
                Console.WriteLine("    Functions String:\t" + FuncStr);
            }
            PWMConfig.ChannelMask = 0xFF;//初始化所有通道
            PWMConfig.Polarity = new byte[8];
            for (int i = 0; i < 8; i++)
            {
                PWMConfig.Polarity[i] = 1;//将所有PWM通道都设置为正极性
            }
            PWMConfig.Precision = new ushort[8];
            for (int i = 0; i < 8; i++)
            {
                PWMConfig.Precision[i] = 100;//将所有通道的占空比调节精度都设置为1%
            }
            PWMConfig.Prescaler = new ushort[8];
            for (int i = 0; i < 8; i++)
            {
                PWMConfig.Prescaler[i] = 10;//将所有通道的预分频器都设置为10，则PWM输出频率为200MHz/(PWMConfig.Precision*PWMConfig.Prescaler)
            }
            PWMConfig.Pulse = new ushort[8];
            for (int i = 0; i < 8; i++)
            {
                PWMConfig.Pulse[i] = (UInt16)(PWMConfig.Precision[i] * 30 / 100);//将所有通道的占空比都设置为30%
            }
            PWMConfig.Phase = new ushort[8];
            for (int i = 0; i < 8; i++)
            {
                PWMConfig.Phase[i] = 0;//波形相位，取值0到Precision-1
            }
            //初始化PWM
            ret = USB2PWM.PWM_Init(DevHandle, ref PWMConfig);
            if (ret != USB2PWM.PWM_SUCCESS)
            {
                Console.WriteLine("Initialize pwm faild!\n");
                Console.ReadLine();
                return;
            }
            else
            {
                Console.WriteLine("Initialize pwm sunccess!\n");
            }
            //启动PWM,RunTimeOfUs之后自动停止，利用该特性可以控制输出脉冲个数，脉冲个数=RunTimeOfUs*200/(PWMConfig.Precision*PWMConfig.Prescaler)
            Int32 RunTimeOfUs = 10000;
            ret = USB2PWM.PWM_Start(DevHandle, PWMConfig.ChannelMask, RunTimeOfUs);
            if (ret != USB2PWM.PWM_SUCCESS)
            {
                Console.WriteLine("Start pwm faild!\n");
                Console.ReadLine();
                return;
            }
            else
            {
                Console.WriteLine("Start pwm sunccess!\n");
            }
            //停止PWM
            ret = USB2PWM.PWM_Stop(DevHandle,PWMConfig.ChannelMask);
            if (ret != USB2PWM.PWM_SUCCESS)
            {
                Console.WriteLine("Stop pwm faild!\n");
                Console.ReadLine();
                return;
            }else{
                Console.WriteLine("Stop pwm sunccess!\n");
            }
            
            //关闭设备
            usb_device.USB_CloseDevice(DevHandle);
        }
    }
}
