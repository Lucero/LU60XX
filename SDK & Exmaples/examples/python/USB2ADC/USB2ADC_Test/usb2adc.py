from ctypes import *
import platform
from usb_device import *

# Error code define
ADC_SUCCESS = 0             # success
ADC_ERR_NOT_SUPPORT = -1    # Lucero not support
ADC_ERR_USB_WRITE_FAIL = -2 # USB write data error
ADC_ERR_USB_READ_FAIL = -3  # USB read data error
ADC_ERR_CMD_FAIL = -4       # execute function error
ADC_ERR_CH_NO_INIT = -5     # the channel not initialize

# Initialize adc
def ADC_Init(DevHandle,Channel,SampleRateHz):
    return Lucero.ADC_Init(DevHandle,Channel,SampleRateHz)

# Read adc data
def ADC_Read(DevHandle,pData,DataNum):
    return Lucero.ADC_Read(DevHandle,pData,DataNum)
