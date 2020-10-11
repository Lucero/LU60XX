#ifndef __USB_DEVICE_H_
#define __USB_DEVICE_H_

//�����豸��Ϣ
typedef struct _DEVICE_INFO
{
    char    FirmwareName[32];   //�̼������ַ���
    char    BuildDate[32];      //�̼�����ʱ���ַ���
    int     HardwareVersion;    //Ӳ���汾��
    int     FirmwareVersion;    //�̼��汾��
    int     SerialNumber[3];    //���������к�
    int     Functions;          //��������ǰ�߱��Ĺ���
}DEVICE_INFO,*PDEVICE_INFO;

//�����ѹ���ֵ
#define POWER_LEVEL_NONE    0   //�����
#define POWER_LEVEL_1V8     1   //���1.8V
#define POWER_LEVEL_2V5     2   //���2.5V
#define POWER_LEVEL_3V3     3   //���3.3V
#define POWER_LEVEL_5V0     4   //���5.0V


#ifdef __cplusplus
extern "C"
{
#endif
/**
  * @brief  ��ʼ��USB�豸����ɨ���豸���������������
  * @param  pDevHandle ÿ���豸���豸�Ŵ洢��ַ
  * @retval ɨ�赽���豸����
  */
int USB_ScanDevice(int *pDevHandle);

/**
  * @brief  ���豸���������
  * @param  DevHandle �豸������
  * @retval ���豸��״̬
  */
bool USB_OpenDevice(int DevHandle);

/**
  * @brief  �ر��豸
  * @param  DevHandle �豸������
  * @retval �ر��豸��״̬
  */
bool USB_CloseDevice(int DevHandle);

/**
  * @brief  ��λ�豸���򣬸�λ����Ҫ���µ���USB_ScanDevice��USB_OpenDevice����
  * @param  DevHandle �豸������
  * @retval ��λ�豸��״̬
  */
bool USB_ResetDevice(int DevHandle);
/**
  * @brief  ��ȡ�豸��Ϣ�������豸���ƣ��̼��汾�ţ��豸��ţ��豸����˵���ַ�����
  * @param  DevHandle �豸������
  * @param  pDevInfo �豸��Ϣ�洢�ṹ��ָ��
  * @param  pFunctionStr �豸����˵���ַ���
  * @retval ��ȡ�豸��Ϣ��״̬
  */
bool DEV_GetDeviceInfo(int DevHandle,PDEVICE_INFO pDevInfo,char *pFunctionStr);

/**
  * @brief  ���ÿɱ��ѹ������������ѹֵ
  * @param  DevHandle �豸������
  * @param  PowerLevel �����ѹֵ
  * @retval ���������ѹ״̬
  */
bool DEV_SetPowerLevel(int DevHandle,char PowerLevel);

#ifdef __cplusplus
}
#endif

#endif

