using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace LUCERO
{
    class USB2ADC
    {
        //定义函数返回错误代码
        public const Int32 ADC_SUCCESS = (0);   //函数执行成功
        public const Int32 ADC_ERR_NOT_SUPPORT = (-1);  //适配器不支持该函数
        public const Int32 ADC_ERR_USB_WRITE_FAIL = (-2);  //USB写数据失败
        public const Int32 ADC_ERR_USB_READ_FAIL = (-3);  //USB读数据失败
        public const Int32 ADC_ERR_CMD_FAIL = (-4);  //命令执行失败
        public const Int32 ADC_ERR_CH_NO_INIT = (-5);  //参数传入错误
        
        //USB2ADC相关函数定义
        /**
          * @brief  初始化配置ADC
          * @param  DevIndex 设备索引号
          * @param  Channel 需要配置的ADC通道，每个bit为对应一个通道，为1时则需要配置该通道，最低位代表通道0
          * @param  SampleRateHz ADC采样率，单通道最大2.5MHz，单位为Hz
          * @retval 函数执行状态，小于0函数执行出错
          */
        [DllImport("LUCERO.dll")]
        public static extern Int32 ADC_Init(Int32 DevIndex,Byte Channel,Int32 SampleRateHz);
        /**
          * @brief  启动并驱动ADC转换值
          * @param  DevIndex 设备索引号
          * @param  pData 数据存储缓冲区首地址
          * @param  DataNum 获取转换的数据数，每个数据之间的时间间隔为初始化配置时候的采样频率决定
          * @retval 函数执行状态，小于0函数执行出错
          */
        [DllImport("LUCERO.dll")]
        public static extern Int32 ADC_Read(Int32 DevIndex, UInt16[] pData, Int32 DataNum);
        
    }
}
