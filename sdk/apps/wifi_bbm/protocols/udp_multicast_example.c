
#include "lwip.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "pairing_data_model.h"
#include "udp_multicast.h"

void multicast_recv_test(int port)
{
    UdpRecvParam udpRecvParam;
    char ip[16];
    int remote_port;
    int ret;
    char *send_data = "Successfully received data!";

    udpRecvParam.buf = (char *)malloc(MULTICAST_BUF);
    if (udpRecvParam.buf == NULL) {
        printf("multicast_test : malloc faile\n");
        return;
    }

    udpRecvParam.len = 1024;
    udpRecvParam.remoteIp = ip;
    udpRecvParam.remotePort = &remote_port;
    udpRecvParam.remoteIpLen = sizeof(ip);

    /*创建组播*/
    udpRecvParam.fd = CreateUdpMulticast(port);
    if (udpRecvParam.fd < 0) {
        printf("CreateUdp fail\n");
        free(udpRecvParam.buf);
        return;
    }

    printf("CreateUdp succ\n");
    while (1) {
        ret = RecvUdp(&udpRecvParam);
        if (ret > 0) {
            printf("received %d bytes form (IP :%s, PORT:%d)\n", ret, udpRecvParam.remoteIp, *udpRecvParam.remotePort);

            //check head
            int payload_len = get_package_payload_len(udpRecvParam.buf);
            if (payload_len > 0) {
                printf("payload_len: %d\n", payload_len);
                printf("payload: %s\n", udpRecvParam.buf + 8);
            }

            //SendUdp(udpRecvParam.fd, send_data, strlen(send_data), udpRecvParam.remoteIp, *udpRecvParam.remotePort);
        } else {
            printf("recv err: %d\n", ret);
        }

    }

    RemoveUdp(udpRecvParam.fd);
    free(udpRecvParam.buf);
}

