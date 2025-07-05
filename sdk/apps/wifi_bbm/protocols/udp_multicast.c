
#include "lwip.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "pairing_data_model.h"
#include "udp_multicast.h"

/*
 * 创建UDP通讯套接字
 * 参数localPort UDP通信端口号
 * 返回值: 返回值小于0 创建失败, 大于等于0 UDP套接字fd
 */
int CreateUdpMulticast(unsigned short localPort)
{
    printf("CreateUdp localPort : %d\n", localPort);
    struct sockaddr_in localAddr;
    struct ip_mreq McastAdrr;
    void *fd = NULL;
    int flags;
    int onOff = 1;

    fd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (fd < 0) {
        printf("CreateUdp : socket create faile\r\n");
        return SOCKET_CREAT_UDP_FD_FAILED;
    }

#if 0  /** 0: 阻塞 1：非阻塞*/
    flags = sock_fcntl(fd, F_GETFL, 0);
    if (flags < 0 || sock_fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        printf("fcntl: %s\n", strerror(errno));
        sock_unreg(fd);
        return SOCKET_CREAT_UDP_FD_FAILED;
    }
#endif

    if (localPort != 0) {
        if (sock_setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&onOff, sizeof(onOff)) != 0) {
            sock_unreg(fd);
            printf("CreateUdp :  setsockopt set SO_REUSEADDR failed\n");
            return SOCKET_CREAT_UDP_FD_FAILED;
        }

        memset(&localAddr, 0, sizeof(struct sockaddr_in));
        localAddr.sin_family = AF_INET;
        localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        localAddr.sin_port = htons(localPort);

        if (sock_bind(fd, (struct sockaddr *)&localAddr, sizeof(struct sockaddr_in)) < 0) {
            sock_unreg(fd);
            printf("CreateUdp : bind port %u failed\n", localPort);
            return SOCKET_CREAT_UDP_FD_FAILED;
        }

        memset(&McastAdrr, 0, sizeof(struct ip_mreq));
        McastAdrr.imr_multiaddr.s_addr = inet_addr(UDP_MULTICAST_ADDR);
        McastAdrr.imr_interface.s_addr = htonl(INADDR_ANY);

        if (sock_setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &McastAdrr, sizeof(McastAdrr)) < 0) {
            sock_unreg(fd);
            printf("CreateUdp:  failed\n");
            return SOCKET_CREAT_UDP_FD_FAILED;
        }
    }

    return (int)fd;
}

/*
 * UDP读取数据
 * 返回值小于0 读取失败, 大于等于0 实际读取的字节数
 */
int RecvUdp(UdpRecvParam *udpRecvParam)
{
    struct sockaddr_in dstaddr;
    int length = 0;
    unsigned int addrlen = sizeof(dstaddr);

    if (udpRecvParam->buf == NULL || udpRecvParam->remoteIp == NULL || udpRecvParam->remotePort == NULL) {
        return SOCKET_NULL_PTR;
    }

    length = (int)(sock_recvfrom(udpRecvParam->fd, udpRecvParam->buf, udpRecvParam->len, 0,
                                 (struct sockaddr *)&dstaddr, &addrlen));
    if (length <= 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
            printf("UDP : No data received , continue reading\r\n");
            return SOCKET_NO_ERROR;
        } else {
            return SOCKET_READ_UDP_PACKET_FAILED;
        }
    }

    udpRecvParam->buf[length] = '\0';

    strncpy(udpRecvParam->remoteIp, inet_ntoa(dstaddr.sin_addr), udpRecvParam->remoteIpLen);
    *udpRecvParam->remotePort = ntohs(dstaddr.sin_port);

    printf("remote IP : %s , Port: %d\n", udpRecvParam->remoteIp, *udpRecvParam->remotePort);

    return length;
}

/*
 * 用于UDP发送数据
 * 参数fd UDP通讯套接字
 * 参数buf 发送的数据
 * 参数len 数据长度
 * 参数remoteIp 目的ip
 * 参数remotePort 目的端口
 * 返回值小于0 发送失败, 大于等于0 实际发送的字节数
 */
int SendUdp(int fd, const unsigned char *buf, unsigned short len, const char *remoteIp,
            unsigned short remotePort)
{
    struct sockaddr_in destAddr;
    int ret = -1;

    if (buf == NULL || remoteIp == NULL) {
        return SOCKET_NULL_PTR;
    }

    memset(&destAddr, 0, sizeof(struct sockaddr_in));
    destAddr.sin_family = AF_INET;
    destAddr.sin_addr.s_addr = inet_addr(remoteIp);
    destAddr.sin_port = htons(remotePort);

    ret = (int)(sock_sendto(fd, buf, len, 0, (struct sockaddr *)&destAddr, sizeof(struct sockaddr_in)));
    if (ret < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR) {
            return SOCKET_NO_ERROR;
        } else {
            return SOCKET_SEND_UDP_PACKET_FAILED;
        }
    }

    return ret;
}

/*
 * 关闭UDP通讯套接字
 * 输入参数int fd UDP通讯套接字
 */
void RemoveUdp(int fd)
{
    sock_unreg(fd);
}

/*重新设置网络接口ip地址*/
void lwip_raw_netif_set_ipaddr(const char *ip_new)
{
    ip4_addr_t ip4_addr;
    ip4addr_aton(ip_new, &ip4_addr);
    lwip_set_netif_ipaddr(WIFI_RAW_NETIF, &ip4_addr);
}
