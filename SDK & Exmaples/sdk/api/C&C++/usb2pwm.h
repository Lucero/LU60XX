#ifndef __USB2PWM_H_
#define __USB2PWM_H_

//�����ʼ��PWM����������
typedef struct _PWM_CONFIG{
  unsigned short Prescaler[8];  //Ԥ��Ƶ��
  unsigned short Precision[8];  //ռ�ձȵ��ھ���,ʵ��Ƶ�� = 200MHz/(Prescaler*Precision)
  unsigned short Pulse[8];      //ռ�ձȣ�ʵ��ռ�ձ�=(Pulse/Precision)*100%
  unsigned short Phase[8];      //������λ��ȡֵ0��Precision-1
  unsigned char  Polarity[8];   //���μ��ԣ�ȡֵ0����1
  unsigned char  ChannelMask;   //ͨ���ţ���Ҫʹ��ĳ��ͨ�������ӦλΪ1�����λ��Ӧͨ��0
}PWM_CONFIG,*PPWM_CONFIG;

//���庯�����ش������
#define PWM_SUCCESS             (0)   //����ִ�гɹ�
#define PWM_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define PWM_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define PWM_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define PWM_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��

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
