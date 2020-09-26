#ifndef __USB2PWM_H_
#define __USB2PWM_H_

//定义初始化PWM的数据类型
typedef struct _PWM_CONFIG{
  unsigned short Prescaler[8];  //预分频器
  unsigned short Precision[8];  //占空比调节精度,实际频率 = 200MHz/(Prescaler*Precision)
  unsigned short Pulse[8];      //占空比，实际占空比=(Pulse/Precision)*100%
  unsigned short Phase[8];      //波形相位，取值0到Precision-1
  unsigned char  Polarity[8];   //波形极性，取值0或者1
  unsigned char  ChannelMask;   //通道号，若要使能某个通道，则对应位为1，最低位对应通道0
}PWM_CONFIG,*PPWM_CONFIG;

//定义函数返回错误代码
#define PWM_SUCCESS             (0)   //函数执行成功
#define PWM_ERR_NOT_SUPPORT     (-1)  //适配器不支持该函数
#define PWM_ERR_USB_WRITE_FAIL  (-2)  //USB写数据失败
#define PWM_ERR_USB_READ_FAIL   (-3)  //USB读数据失败
#define PWM_ERR_CMD_FAIL        (-4)  //命令执行失败

#ifdef __cplusplus
extern "C"
{
#endif
int PWM_Init(int DevHandle, PPWM_CONFIG pConfig);
int PWM_Start(int DevHandle,unsigned char ChannelMask,unsigned int RunTimeUs);
int PWM_SetPulse(int DevHandle,unsigned char ChannelMask,unsigned short *pPulse);
int PWM_SetPhase(int DevHandle,unsigned char ChannelMask,unsigned short *pPhase);
int PWM_SetFrequency(int DevHandle,unsigned char ChannelMask,unsigned short *pPrescaler,unsigned short *pPrecision);
int PWM_Stop(int DevHandle,unsigned char ChannelMask);

#ifdef __cplusplus
}
#endif
#endif
