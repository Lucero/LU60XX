#ifndef __USB2IIC_H_
#define __USB2IIC_H_

//�����ʼ��IIC����������
typedef struct _IIC_CONFIG{
  unsigned int    ClockSpeedHz; //IICʱ��Ƶ��:��λΪHz
  unsigned short  OwnAddr;      //USB2XXXΪ�ӻ�ʱ�Լ��ĵ�ַ
  unsigned char   Master;       //����ѡ�����:0-�ӻ���1-����
  unsigned char   AddrBits;     //�ӻ���ַģʽ��7-7bitģʽ��10-10bitģʽ
  unsigned char   EnablePu;     //ʹ������оƬ�ڲ��������裬����ʹ�ܣ���I2C�����ϱ������������
}IIC_CONFIG,*PIIC_CONFIG;

//���庯�����ش������
#define IIC_SUCCESS             (0)   //����ִ�гɹ�
#define IIC_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define IIC_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define IIC_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define IIC_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��
#define IIC_ERR_PARA_ERROR      (-5)  //�����������
//����IIC�������ش������
#define IIC_ERROR_SUCCESS     0   //�����ɹ�
#define IIC_ERROR_CHANNEL     1   //��ͨ����֧�ָú���
#define IIC_ERROR_BUSY        2   //����æ
#define IIC_ERROR_START_FAILD 3   //��������ʧ��
#define IIC_ERROR_TIMEOUT     4   //��ʱ
#define IIC_ERROR_NACK        5   //�ӻ���Ӧ��
#define IIC_ERROR_PEC         6   //PECУ��ʧ��

#ifdef __cplusplus
extern "C"
{
#endif
int IIC_Init(int DevHandle,int IICIndex, PIIC_CONFIG pConfig);
int IIC_GetSlaveAddr(int DevHandle,int IICIndex,short *pSlaveAddr);
int IIC_WriteBytes(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pWriteData,int WriteLen,int TimeOutMs);
int IIC_ReadBytes(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pReadData,int ReadLen,int TimeOutMs);
int IIC_WriteReadBytes(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pWriteData,int WriteLen,unsigned char *pReadData,int ReadLen,int TimeOutMs);

#ifdef __cplusplus
}
#endif
#endif
