# AC792N 系列VIDEO&AUDIO&WiFi&蓝牙 AIoT固件程序



快速开始
------------

欢迎使用杰理AC792开源项目，在开始进入项目之前，请详细阅读以下芯片介绍获得对AC792系列芯片大概认识，SDK固件包不含开发文档，进行开发之前详细阅读[SDK开发文档](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/index.html)，为用户提供完善的开发例程，帮助开发者快速顺利地使用AC792系列芯片进行方案开发。



芯片概述
------------

杰理AC792系列是一款低成本高集成度WiFi  802.11b/g/n以及双模蓝牙V2.1到V5.4组合的音视频多媒体系统级Soc。内部集成了主频高达360MHz的双核浮点DSP处理器，自带D-cache、I-cache为各类方案提供了强大的运算能力；并完整支持了单天线40MHz BW WiFi 802.11b/g/n  AP和STA各种通讯模式；通过内部集成PTA共存分时设计模块，使得WiFi/蓝牙V2.1/蓝牙V5.4可同时工作，实现灵活和高性能的无线传输能力；芯片同时集成ADC/DAC接口作为音频处理资源、摄像头接口作为视频处理资源、MIPI/RGB推屏接口作为UI显示资源，方便实现各种高集成度的音视频多媒体处理方案，同时自带PMU模块提供多种低功耗工作模式，能使用LDO或者DCDC供电模式满足不同方案供电管理需求。



芯片应用场景
------------

- 儿童绘本故事机
- 大屏智能音箱
- 点读笔/扫描笔/翻译笔
- WiFi蓝牙智能音箱
- 可视门铃/视频门锁/楼宇智能
- WiFi监控摄像头IP Camera
- WiFi可视美容仪
- 蓝牙/USB扫码枪
- 婴儿监护器
- 宠物喂食机
- WiFi摄像头玩具
- 智能家居/物联网设备



芯片软硬件资源介绍
------------

### CPU

- 双核DSP，最高主频360Mhz，支持单精度浮点以及数学运算加速引擎，带I-cache、D-cache，片上集成了共384K字节SRAM，封装支持8/16M Bytes DDR1

  

### 外设

- GPIO、IIC、SPI、SDIO、PWM、MCPWM、UART、CAN、USB1.1、USB2.0、ADC、TIMER、IR接收、电容触摸按键、旋转编码器、GPCNT、RTC、Ethernet、LEDC

  

### MATH

- 支持硬件FFT、IFFT、矩阵运算

- 支持硬件AES 128/192/256，支持ECB、CBC、CTR、CFB128、OFB、GCM、GMAC、CCM、XTS模式

- 支持硬件SHA128/256

- 支持硬件随机数

- 支持硬件CRC，多项式位数支持7位、8位、16位、32位，支持输入/输出数据位反转，输入数据端序翻转

  

### 蓝牙

- 双模蓝牙V5.4规范

- 支持AoA和AoD

- 支持LE audio BIS/CIS

- 发射功率最高可到达+19dbm

- 接收器灵敏度: BR -97dBm, EDR π/4 DQPSK -96dBm, EDR 8DPSK -88dBm

  

### WiFi

- 支持 IEEE 802.11b/g/n

- 802.11n支持 MCS0~ MCS7、20MHz/40MHz 带宽

- 支持800ns 和 400ns 保护间隔

- 支持AP模式、STA模式、monitor配网模式

- AP模式支持多个基站接入

- STA模式支持保存多个连接网络，匹配信号最好的网络去连接

- 支持STA模式冷启动快连

- 支持power save mode省电模式

- 支持WPA/WPA2/WPA3-Personal安全模式及其混合模式

- 支持脱离802.11协议，直接利用底层RF收发数据包

- 支持连接CMW270/极致汇仪等测试仪测试板子RF性能

- 发射功率: 

  DSSS 1M/S             19  dBm 

  MCS0                       17  dBm 

  MCS7                       13 dBm

- 接收灵敏度: 

  DSSS 1M/S             -96  dBm

   MCS0                       -93  dBm 

  MCS7                       -74  dBm

  

### 音频

- 集成DAC(需要外挂功放)、MIC、LINEIN、IIS、PDM音频硬件模块，其中IIS模块支持4个通道同时工作，可单独设置成输入或者输出、支持16/24bit数据位宽 PDMLINK模块支持同时接入2路16bit数据位宽的数字麦，ADC支持2个通道同时工作，每通道皆可支持配置成MIC或者LINEIN
- 支持SBC、MSBC、CVSD、AAC、MP2、MP3、ADPCM、AMR、OPUS、OGG、SPX、WAV、PCM音频编码格式，编码数据源支持MIC、LINEIN、IIS、PDMLINK和虚拟数据源
- 支持SBC、MSBC、CVSD、AAC、ADPCM、AMR、APE、DTS、FLAC、M4A、MP1、MP2、MP3、OPUS、OGG、SPX、WAV、WMA、PCM音频解码格式，解码数据源支持FLASH、SD卡、U盘、LINEIN、外挂FM模块、网络URL、经典蓝牙、虚拟数据源、客户自定义解密数据源
- 音效处理支持混响、回声、电音、变声变调、变速、移频、啸波抑制、EQ、DRC、回声消除、传统降噪、神经网络降噪
- 语音识别支持活动语音检测VAD、单/双mic的打断唤醒ASR功能
- 部分解码格式支持断点播放、快进快退、定点播放、AB点复读播放



### 视频

- 支持2路DVP-1/2/4/8bit、 BT656图像传感器接口的YUV sensor，最大支持720P分辨率
- 支持MIPI 1 LANE sensor，最大支持720P分辨率
- 支持JPEG编码流最大720P@30fps@AVI封装
- 支持JPEG单张最大编解分辨率16384x16384
- 支持最大三路组合MIPI+DVP+UVC，MIPI+DVP+DVP
- 支持四路缩放,最大支持720P，其中2路支持OSD
- 支持图像信号处理(ISP)，黑电平校正，去坏点，2D降噪，色度降噪，锐化，亮度对比度，颜色矩阵，白平衡，自动曝光，伽马曲线，镜头阴影校正



### 显示

- 推屏接口支持MIPI DSI (1~4Lane)、并行数据接口(8bit/16bit)、 RGB888(8bit/24bit)、  YUV888(24bit)、RGB666(9bit/18bit)、RGB565(8bit/16bit)、YUV422(8bit/16bit)、 RGB333(9bit)，最高推屏帧率可达1280x800@30+fps
- 可支持屏触摸、竖屏横显、UI和摄像头图像合成叠加显示
- 屏显支持颜色增强，支持亮度，饱和度、对比度等多样化效果设置
- 支持开源UI框架LVGL，适配支持DMA2D/GPU2.5D 图形加速器，支持杰理LVGL可视化UI编辑工具自动生成LVGL代码
- 支持开源UI框架AWTK，适配支持DMA2D/GPU2.5D 图形加速器
- 支持GPU2.5D矢量绘图，图像2.5D变换



###  网络协议栈

- 基础协议支持:lwip、mbedtls、http/https、websocket、coap、nopoll、curl、mqtt、ftp、uip、iperf

- AI云平台支持:图灵、百度云、腾讯云、中国电信智能家居平台、涂鸦、阿里云、华为hilink、天猫精灵、亚马逊平台、思必弛、玩瞳

  

### 固件升级

- 支持不备份升级和备份升级；

- 不备份升级支持通过存储设备（如：SD卡、U盘）的方式进行升级；

- 备份升级支持通过存储设备（如：SD卡、U盘）和无线网络（如：Wi-Fi，蓝牙）的方式进行升级；

- 备份升级支持UBOOT备份升级；

  

### SDK中间件

- FAT文件系统
- 数据存储记忆
- Pthread API
- 循环CBUF
- 帧LBUF



参考资源
------------

* 芯片数据手册&原理图 : [doc/datasheet/AC792N规格书](./doc/硬件资料/datasheet)
* SDK 发布版本信息 : [AC79NN_SDK_发布版本信息](https://doc.zh-jieli.com/AC792/zh-cn/wifi_video_master/other/version/index.html)
* 钉钉技术支持群号 : 91050006452
