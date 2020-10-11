#ifndef __USB2ADC_H_
#define __USB2ADC_H_

//���庯�����ش������
#define ADC_SUCCESS             (0)   //����ִ�гɹ�
#define ADC_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define ADC_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define ADC_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define ADC_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��
#define ADC_ERR_CH_NO_INIT      (-5)  //��ͨ��δ��ʼ��


#ifdef __cplusplus
extern "C"
{
#endif
/**
  * @brief  ��ʼ������ADC
  * @param  DevHandle �豸������
  * @param  Channel ��Ҫ���õ�ADCͨ����ÿ��bitΪ��Ӧһ��ͨ����Ϊ1ʱ����Ҫ���ø�ͨ�������λ����ͨ��0
  * @param  SampleRateHz ADC�����ʣ���ͨ�����2.5MHz����λΪHz
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int ADC_Init(int DevHandle,char Channel,int SampleRateHz);
/**
  * @brief  ����������ADCת��ֵ
  * @param  DevHandle �豸������
  * @param  pData ���ݴ洢�������׵�ַ
  * @param  DataNum ��ȡת������������ÿ������֮���ʱ����Ϊ��ʼ������ʱ��Ĳ���Ƶ�ʾ���
  * @retval ����ִ��״̬��С��0����ִ�г���
  */
int ADC_Read(int DevHandle,short *pData,int DataNum);

#ifdef __cplusplus
}
#endif
#endif

