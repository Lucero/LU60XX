using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace LUCERO
{
    class usb_device
    {
        //定义电压输出值
        public const Byte POWER_LEVEL_NONE = 0;	//不输出
        public const Byte POWER_LEVEL_1V8 = 1;	//输出1.8V
        public const Byte POWER_LEVEL_2V5 = 2;	//输出2.5V
        public const Byte POWER_LEVEL_3V3 = 3;	//输出3.3V
        public const Byte POWER_LEVEL_5V0 = 4;	//输出5.0V
        //设备信息定义
        public struct DEVICE_INFO
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public Byte[] FirmwareName;   //固件名称字符串
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
            public Byte[]   BuildDate;    //固件编译时间字符串
            public UInt32 HardwareVersion;//硬件版本号
            public UInt32 FirmwareVersion;//固件版本号
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
            public UInt32[] SerialNumber; //适配器序列号
            public UInt32 Functions;      //适配器当前具备的功能
        }
        //方法定义
        /**
          * @brief  初始化USB设备，并扫描设备连接数，必须调用
          * @param  pDevHandle 每个设备的设备号存储地址
          * @retval 扫描到的设备数量
          */
        [DllImport("LUCERO.dll")]
        public static extern Int32 USB_ScanDevice(Int32[] pDevHandle);
        /**
          * @brief  打开设备，必须调用
          * @param  DevHandle 设备索引号
          * @retval 打开设备的状态
          */
        [DllImport("LUCERO.dll")]
        public static extern bool USB_OpenDevice(Int32 DevHandle);
        /**
          * @brief  关闭设备
          * @param  DevHandle 设备索引号
          * @retval 关闭设备的状态
          */
        [DllImport("LUCERO.dll")]
        public static extern bool USB_CloseDevice(Int32 DevHandle);
        /**
          * @brief  复位设备程序，复位后需要重新调用USB_ScanDevice，USB_OpenDevice函数
          * @param  DevHandle 设备索引号
          * @retval 复位设备的状态
          */
        [DllImport("LUCERO.dll")]
        public static extern bool USB_ResetDevice(Int32 DevHandle);
        /**
          * @brief  获取设备信息，比如设备名称，固件版本号，设备序号，设备功能说明字符串等
          * @param  DevHandle 设备索引号
          * @param  pDevInfo 设备信息存储结构体指针
          * @param  pFunctionStr 设备功能说明字符串
          * @retval 获取设备信息的状态
          */
        [DllImport("LUCERO.dll")]
        public static extern bool DEV_GetDeviceInfo(Int32 DevHandle, ref DEVICE_INFO pDevInfo, StringBuilder pFunctionStr);
        
        /**
          * @brief  设置可变电压输出引脚输出电压值
          * @param  DevHandle 设备索引号
          * @param  PowerLevel 输出电压值
          * @retval 设置输出电压状态
          */
        [DllImport("LUCERO.dll")]
        public static extern bool DEV_SetPowerLevel(Int32 DevHandle,byte PowerLevel);
    }
}
