from ctypes import *
import platform
from usb_device import *

# Error code define
PWM_SUCCESS = 0             # success
PWM_ERR_NOT_SUPPORT = -1    # Lucero not support
PWM_ERR_USB_WRITE_FAIL = -2 # USB write data error
PWM_ERR_USB_READ_FAIL = -3  # USB read data error
PWM_ERR_CMD_FAIL = -4       # execute function error

# PWM初始化配置参数
class PWM_CONFIG(Structure):  
    _fields_ = [
        ("Prescaler", c_ushort*8),   # 预分频器
        ("Precision", c_ushort*8),   # 占空比调节精度
        ("Pulse", c_ushort*8),       # 占空比，实际占空比=(Pulse/Precision)*100%
        ("Phase",c_ushort*8),         # 波形相位，取值0到Precision-1
        ("Polarity",c_ubyte*8),      # 波形极性
        ("ChannelMask",c_ubyte)      # 使能的通道号，每个通道对应一个bit位，bit0对应PWM_CH1
    ]


# Initialize pwm
def PWM_Init(DevHandle,pConfig):
    return Lucero.PWM_Init(DevHandle,pConfig)

# 启动PWM
def PWM_Start(DevHandle,ChannelMask,RunTimeOfUs):
    return Lucero.PWM_Start(DevHandle,ChannelMask,RunTimeOfUs)

# 停止PWM
def PWM_Stop(DevHandle,ChannelMask):
    return Lucero.PWM_Stop(DevHandle,ChannelMask)

# 改变脉冲宽度
def PWM_SetPulse(DevHandle,ChannelMask,pPulse):
    return Lucero.PWM_SetPulse(DevHandle,ChannelMask,pPulse)
# 改变相位
def PWM_SetPhase(DevHandle,ChannelMask,pPhase):
    return Lucero.PWM_SetPhase(DevHandle,ChannelMask,pPhase)
# 改变频率
def PWM_SetFrequency(DevHandle,ChannelMask,pPrescaler,pPrecision):
    return Lucero.PWM_SetFrequency(DevHandle,ChannelMask,pPrescaler,pPrecision)
# 改独立输出脉冲信号
def PWM_SendPulses(DevHandle,PinMask,PulseWidthUs,PulsePeriodUs,PulseNum):
    return Lucero.PWM_SendPulses(DevHandle,PinMask,PulseWidthUs,PulsePeriodUs,PulseNum)
