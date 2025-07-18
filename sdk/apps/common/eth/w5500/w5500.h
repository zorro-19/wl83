#ifndef	_W5500_H_
#define	_W5500_H_

#include "gpio.h"
#include <stdio.h>
#include "includes.h"
#include "os/os_api.h"
#include "w5500_socket.h"
#include "asm/port_waked_up.h"

/***************----- W5500 SPI设备定义 -----***************/
#define OS_SUPPORT 		1	//支持操作系统
#define SPI_USE_DEV		1	//使用dev设备接口
#if SPI_USE_DEV
#define SPI_DEV_NAME	"spi2" //spi设备名称，SPI速度 < 30MHz
#endif

/*board.c的SPI设备配置
SPI2_PLATFORM_DATA_BEGIN(spi2_data)
	.clk    = 24000000,
	.mode   = SPI_STD_MODE,
    .attr	= SPI_SCLK_L_UPL_SMPH,
    .role   = SPI_MODE_MASTER,
	.port   = 'C',
SPI2_PLATFORM_DATA_END()
*/

/***************----- W5500 GPIO定义 -----***************/
#define W5500_RST_IO   	IO_PORTA_05 //定义W5500的RST引脚
#define W5500_CS_IO    	IO_PORTA_01 //定义W5500的CS引脚
#define W5500_SCLK_IO  	IO_PORTA_03 //定义W5500的SCLK引脚
#define W5500_MISO_IO  	IO_PORTA_02 //定义W5500的MISO引脚
#define W5500_MOSI_IO  	IO_PORTA_04 //定义W5500的MOSI引脚
#define W5500_INT_IO   	IO_PORTA_00 //定义W5500的INT引脚

#define W5500_INT_EVENT	EVENT_IO_0 //中断引脚中断事件:EVENT_IO_0和EVENT_IO_1任意IO
#define W5500_INT_EDGE	EDGE_NEGATIVE //中断引脚边沿触发:EDGE_NEGATIVE下降沿,EDGE_POSITIVE上升沿

#define W5500_RST_SET(x)  gpio_direction_output(W5500_RST_IO,x)
#define W5500_INT_SET(x)  gpio_direction_output(W5500_INT_IO,x)
#define W5500_CS_SET(x)   gpio_direction_output(W5500_CS_IO,x)
#define W5500_SCLK_SET(x) gpio_direction_output(W5500_SCLK_IO,x)
#define W5500_MISO_SET(x) gpio_direction_output(W5500_MISO_IO,x)
#define W5500_MISO_GET()  gpio_read(W5500_MISO_IO)
#define W5500_MOSI_SET(x) gpio_direction_output(W5500_MOSI_IO,x)
#define W5500_SCLK_SET_HD(x) gpio_set_hd(W5500_SCLK_IO,x)

/***************----- W5500 IO初始化 -----***************/
#define W5500_IO_INIT() \
{\
	gpio_direction_output(W5500_RST_IO,1);\
	gpio_direction_input(W5500_INT_IO);\
	gpio_direction_output(W5500_CS_IO,1);\
	gpio_direction_output(W5500_SCLK_IO,1);\
	gpio_direction_input(W5500_MISO_IO);\
	gpio_direction_output(W5500_MOSI_IO,1);\
}

/*******----- W5500 printf w5500_delay_ms -----************/
#define w5500_log	printf
#if OS_SUPPORT
#define w5500_delay_ms(x)	 	os_time_dly(x/10)
#else
#define w5500_delay_ms(x)	 	delay_ms(x)
#endif
#define w5500_delay_us			delay_us
#define delay_ms				w5500_delay_ms
#define socket_delay_ms(x)	 	w5500_delay_ms(x)


/***************----- W5500寄存器 -----********************/
/***************** Common Register *****************/
#define MR		0x0000
#define RST		0x80
#define WOL		0x20
#define PB		0x10
#define PPP		0x08
#define FARP	0x02

#define GAR		0x0001
#define SUBR	0x0005
#define SHAR	0x0009
#define SIPR	0x000f

#define INTLEVEL	0x0013
#define IR		0x0015
#define CONFLICT	0x80
#define UNREACH		0x40
#define PPPOE		0x20
#define MP			0x10

#define IMR		0x0016
#define IM_IR7		0x80
#define IM_IR6		0x40
#define IM_IR5		0x20
#define IM_IR4		0x10

#define SIR		0x0017
#define S7_INT		0x80
#define S6_INT		0x40
#define S5_INT		0x20
#define S4_INT		0x10
#define S3_INT		0x08
#define S2_INT		0x04
#define S1_INT		0x02
#define S0_INT		0x01

#define SIMR	0x0018
#define S7_IMR		0x80
#define S6_IMR		0x40
#define S5_IMR		0x20
#define S4_IMR		0x10
#define S3_IMR		0x08
#define S2_IMR		0x04
#define S1_IMR		0x02
#define S0_IMR		0x01

#define RTR		0x0019
#define RCR		0x001b

#define PTIMER	0x001c
#define PMAGIC	0x001d
#define PHA		0x001e
#define PSID	0x0024
#define PMRU	0x0026

#define UIPR	0x0028
#define UPORT	0x002c

#define PHYCFGR	0x002e
#define RST_PHY		0x80
#define OPMODE		0x40
#define DPX			0x04
#define SPD			0x02
#define LINK		0x01

#define VERR	0x0039

/********************* Socket Register *******************/
#define Sn_MR		0x0000
#define MULTI_MFEN		0x80
#define BCASTB			0x40
#define	ND_MC_MMB		0x20
#define UCASTB_MIP6B	0x10
#define MR_CLOSE		0x00
#define MR_TCP		0x01
#define MR_UDP		0x02
#define MR_MACRAW		0x04

#define Sn_CR		0x0001
#define OPEN		0x01
#define LISTEN		0x02
#define CONNECT		0x04
#define DISCON		0x08
#define CLOSE		0x10
#define SEND		0x20
#define SEND_MAC	0x21
#define SEND_KEEP	0x22
#define RECV		0x40

#define Sn_IR		0x0002
#define IR_SEND_OK		0x10
#define IR_TIMEOUT		0x08
#define IR_RECV			0x04
#define IR_DISCON		0x02
#define IR_CON			0x01

#define Sn_SR		0x0003
#define SOCK_CLOSED		0x00
#define SOCK_INIT		0x13
#define SOCK_LISTEN		0x14
#define SOCK_ESTABLISHED	0x17
#define SOCK_CLOSE_WAIT		0x1c
#define SOCK_UDP		0x22
#define SOCK_MACRAW		0x02

#define SOCK_SYNSEND	0x15
#define SOCK_SYNRECV	0x16
#define SOCK_FIN_WAI	0x18
#define SOCK_CLOSING	0x1a
#define SOCK_TIME_WAIT	0x1b
#define SOCK_LAST_ACK	0x1d

#define Sn_PORT		0x0004
#define Sn_DHAR	   	0x0006
#define Sn_DIPR		0x000c
#define Sn_DPORTR	0x0010

#define Sn_MSSR		0x0012
#define Sn_TOS		0x0015
#define Sn_TTL		0x0016

#define Sn_RXBUF_SIZE	0x001e
#define Sn_TXBUF_SIZE	0x001f
#define Sn_TX_FSR	0x0020
#define Sn_TX_RD	0x0022
#define Sn_TX_WR	0x0024
#define Sn_RX_RSR	0x0026
#define Sn_RX_RD	0x0028
#define Sn_RX_WR	0x002a

#define Sn_IMR		0x002c
#define IMR_SENDOK	0x10
#define IMR_TIMEOUT	0x08
#define IMR_RECV	0x04
#define IMR_DISCON	0x02
#define IMR_CON		0x01

#define Sn_FRAG		0x002d
#define Sn_KPALVTR	0x002f

/*******************************************************************/
/************************ SPI Control Byte *************************/
/*******************************************************************/
/* Operation mode bits */
#define VDM		0x00
#define FDM1	0x01
#define	FDM2	0x02
#define FDM4	0x03

/* Read_Write control bit */
#define RWB_READ	0x00
#define RWB_WRITE	0x04

/* Block select bits */
#define COMMON_R	0x00

/* Socket 0 */
#define S0_REG		0x08
#define S0_TX_BUF	0x10
#define S0_RX_BUF	0x18

/* Socket 1 */
#define S1_REG		0x28
#define S1_TX_BUF	0x30
#define S1_RX_BUF	0x38

/* Socket 2 */
#define S2_REG		0x48
#define S2_TX_BUF	0x50
#define S2_RX_BUF	0x58

/* Socket 3 */
#define S3_REG		0x68
#define S3_TX_BUF	0x70
#define S3_RX_BUF	0x78

/* Socket 4 */
#define S4_REG		0x88
#define S4_TX_BUF	0x90
#define S4_RX_BUF	0x98

/* Socket 5 */
#define S5_REG		0xa8
#define S5_TX_BUF	0xb0
#define S5_RX_BUF	0xb8

/* Socket 6 */
#define S6_REG		0xc8
#define S6_TX_BUF	0xd0
#define S6_RX_BUF	0xd8

/* Socket 7 */
#define S7_REG		0xe8
#define S7_TX_BUF	0xf0
#define S7_RX_BUF	0xf8

//#define TRUE	0xff
//#define FALSE	0x00

#define S_RX_SIZE	2048	/*定义Socket接收缓冲区的大小，可以根据W5500_RMSR的设置修改 */
#define S_TX_SIZE	2048  	/*定义Socket发送缓冲区的大小，可以根据W5500_TMSR的设置修改 */


typedef unsigned char SOCKET;			//自定义端口号数据类型

extern unsigned int W5500_ip_addr_get(void);
extern void W5500_Hardware_Reset(void);//硬件复位W5500
extern void W5500_Init(void);//初始化W5500寄存器函数
extern unsigned char Socket_Connect(SOCKET s);//设置指定Socket(0~7)为客户端与远程服务器连接
extern unsigned char Socket_Listen(SOCKET s);//设置指定Socket(0~7)作为服务器等待远程主机的连接
extern unsigned char Socket_UDP(SOCKET s);//设置指定Socket(0~7)为UDP模式
extern unsigned short Read_SOCK_Data_Buffer(SOCKET s, unsigned char *dat_ptr);//指定Socket(0~7)接收数据处理
extern void Write_SOCK_Data_Buffer(SOCKET s, unsigned char *dat_ptr, unsigned short size); //指定Socket(0~7)发送数据处理
extern void Write_W5500_nByte(unsigned short reg, unsigned char *dat_ptr, unsigned short size);
extern void Write_W5500_SOCK_1Byte(SOCKET s, unsigned short reg, unsigned char dat);
extern void Write_W5500_SOCK_2Byte(SOCKET s, unsigned short reg, unsigned short dat);
extern void Write_W5500_SOCK_4Byte(SOCKET s, unsigned short reg, unsigned char *dat_ptr);
extern void Write_W5500_1Byte(unsigned short reg, unsigned char dat);
extern void Write_W5500_2Byte(unsigned short reg, unsigned short dat);
extern void Write_W5500_nByte(unsigned short reg, unsigned char *dat_ptr, unsigned short size);
extern unsigned char Read_W5500_1Byte(unsigned short reg);
extern unsigned char Read_W5500_SOCK_1Byte(SOCKET s, unsigned short reg);
extern unsigned short Read_W5500_SOCK_2Byte(SOCKET s, unsigned short reg);
#endif

