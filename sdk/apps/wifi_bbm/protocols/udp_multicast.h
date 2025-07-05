
#ifndef UDP_MULTICAST_H_
#define UDP_MULTICAST_H_

#ifdef __cplusplus
extern "C" {
#endif

/* udp读取数据参数结构体 */
typedef struct {
    int fd;                 /* UDP通讯套接字 */
    unsigned char *buf;     /* 存放数据的缓冲 */
    unsigned short len;     /* 要读取的长度 */
    char *remoteIp;              /* 远端ip */
    unsigned short remoteIpLen;  /* 远端ip长度 */
    unsigned short *remotePort;   /* 远端端口 */
} UdpRecvParam;

/*Socket错误码 */
typedef enum {
    SOCKET_NO_ERROR = 0,
    SOCKET_NULL_PTR = -1,
    SOCKET_CREAT_UDP_FD_FAILED = -2,
    SOCKET_SEND_UDP_PACKET_FAILED = -3,
    SOCKET_READ_UDP_PACKET_FAILED = -4,
    SOCKET_TCP_CONNECTING = -5,
    SOCKET_TCP_CONNECT_FAILED = -6,
    SOCKET_SEND_TCP_PACKET_FAILED = -7,
    SOCKET_READ_TCP_PACKET_FAILED = -8,
    SOCKET_REMOVE_UDP_FD_FAILED = -9,
    SOCKET_SELECT_TIMEOUT = -10,
    SOCKET_SELECT_ERROR = -11
} socket_error_t;

#define LOCAL_PORT 32768
#define MULTICAST_BUF 1024

/** 组播地址*/
#define UDP_MULTICAST_ADDR "238.238.238.238"

#ifdef __cplusplus
}
#endif

#endif
