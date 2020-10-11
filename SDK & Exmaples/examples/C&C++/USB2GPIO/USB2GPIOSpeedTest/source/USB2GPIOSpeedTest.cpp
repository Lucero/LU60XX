#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usb2gpio.h"
#include "usb_device.h"


int main(int argc, const char* argv[])
{
    DEVICE_INFO DevInfo;
    int DevHandle[10];
    bool state;
    int ret;
    unsigned int PinValue;
    //ɨ������豸
    ret = USB_ScanDevice(DevHandle);
    if(ret <= 0){
        printf("No device connected!\n");
        return 0;
    }
    //���豸
    state = USB_OpenDevice(DevHandle[0]);
    if(!state){
        printf("Open device error!\n");
        return 0;
    }
    //��ȡ�̼���Ϣ
    char FuncStr[256]={0};
    state = DEV_GetDeviceInfo(DevHandle[0],&DevInfo,FuncStr);
    if(!state){
        printf("Get device infomation error!\n");
        return 0;
    }else{
        printf("Firmware Info:\n");
        printf("    Name:%s\n",DevInfo.FirmwareName);
        printf("    Build Date:%s\n",DevInfo.BuildDate);
        printf("    Version:v%d.%d.%d\n",(DevInfo.FirmwareVersion>>24)&0xFF,(DevInfo.FirmwareVersion>>16)&0xFF,DevInfo.FirmwareVersion&0xFFFF);
        printf("    Version:v%d.%d.%d\n",(DevInfo.HardwareVersion>>24)&0xFF,(DevInfo.HardwareVersion>>16)&0xFF,DevInfo.HardwareVersion&0xFFFF);
        printf("    Functions:%08X\n",DevInfo.Functions);
        printf("    Functions:%s\n",FuncStr);
    }
    //������ԡ���û������
    GPIO_SetOutput(DevHandle[0],0xFFFF,1);
    //��ȡ��ʼʱ��,��Ҫ���ڲ��Է����ٶ�
    LARGE_INTEGER litmp;
    LONGLONG StartTime,EndTime;
    double dfFreq;
    int TestNum = 10000;
    CRITICAL_SECTION  _critical;
    /*��ʼ�������ȵ��õĺ�����ûʲô��˵�ģ�һ��windows��̶������Ƴ�ʼ���ķ���*/
    InitializeCriticalSection(&_critical);
    /*
    �Ѵ��뱣�����������ô˺��������Ժ����Դ�����߳̾Ͳ��ܷ����ˡ�
    */
    EnterCriticalSection(& _critical);
    FILE *fp;
    if((fp=fopen("GPIOSpeed.csv","wt"))==NULL){
        printf("Cannot open file strike any key exit!\n");
        getchar();
        exit(1);
    }
    int max0=0;//����ʱ��С��1ms�Ĵ���
    int max1=0;//����ʱ��С��2ms������1ms�Ĵ���
    int max2=0;//����ʱ��С��3ms������2ms�Ĵ���
    int max3=0;//����ʱ��С��4ms������3ms�Ĵ���
    int max4=0;//���ƴ���4ms�Ĵ���
    for(int i=0;i<TestNum;i++){
        QueryPerformanceFrequency(&litmp);// Get the performance counter frequency, in n/s
        dfFreq = (double)litmp.QuadPart;
        QueryPerformanceCounter(&litmp);  // Get the current value of the performance counter
        StartTime = litmp.QuadPart;       // Start time
        GPIO_Write(DevHandle[0],0xFFFF,0xFFFF);
        QueryPerformanceCounter(&litmp);// Get the current value of the performance counter
        EndTime = litmp.QuadPart; // Stop time
        float time = 1000*((EndTime-StartTime)/dfFreq);
        //GPIO_Write(DevHandle[0],0xFFFF,0x0000);
        fprintf(fp,"%f\n",time);
        if(time>=4){
            max4++;
        }else if(time>=3){
            max3++;
        }else if(time>=2){
            max2++;
        }else if(time>=1){
            max1++;
        }else{
            max0++;
        }
    }
    fclose(fp);
    printf("����ʱ�����4ms�Ĵ��� = %d\n",max4);
    printf("����ʱ�����3ms,С��4ms�Ĵ��� = %d\n",max3);
    printf("����ʱ�����2ms,С��3ms�Ĵ���  = %d\n",max2);
    printf("����ʱ�����1ms,С��2ms�Ĵ���  = %d\n",max1);
    printf("����ʱ��С��1ms�Ĵ���  = %d\n",max0);
    /*
    �뿪�ٽ�������ʾ�����߳��ܹ������ˡ�ע��EnterCritical��LeaveCrticalSection�����ǳɶԳ��ֵ�!��Ȼ�������������������
    */
    LeaveCriticalSection(&_critical);
    /*�ͷ���Դ��ȷ����ʹ��_criticalʱ���ã�һ���ڳ����˳���ʱ����á�����Ժ�Ҫ��_critical����Ҫ���µ���InitializeCriticalSection
    */
    DeleteCriticalSection(&_critical); 

    //�ر��豸
    USB_CloseDevice(DevHandle[0]);
    return 0;
}

