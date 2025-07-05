#include "app_config.h"

#if TCFG_ETH_ENABLE

#include "system/init.h"
#include "device/device.h"
#include "lwip.h"
#include "eth/eth_phy.h"
#include "event/device_event.h"
#include "os/os_api.h"


static void eth_network_test(void);

int eth_lwip_event_cb(void *lwip_ctx, enum LWIP_EVENT event)
{
    char ip_addr[32];
    char gw_addr[32];

    switch (event) {
    case LWIP_WIRE_DHCP_BOUND_TIMEOUT:
        break;

    case LWIP_WIRE_DHCP_BOUND_SUCC:
        Get_IPAddress(ETH_NETIF, ip_addr);
        get_gateway(ETH_NETIF, gw_addr);
        printf("ETH DHCP SUCC, IP:[%s] , GW:[%s]", ip_addr, gw_addr);
        lwip_set_default_netif(ETH_NETIF);
        break;

    default:
        break;
    }

    return 0;
}

static int eth_state_cb(void *priv, eth_event_t event)
{
    switch (event) {
    case ETH_EVENT_LINK_ON:
        printf("ETH_EVENT_LINK_ON");
        /* eth_network_test(); */
        break;

    case ETH_EVENT_LINK_OFF:
        printf("ETH_EVENT_LINK_OFF");
        break;

    default:
        return -1;
    }

    return 0;
}

static void eth_set_lan_setting_info(void *device)
{
    struct lan_setting lan_setting_info = {
        .WIRELESS_IP_ADDR0  = 172,
        .WIRELESS_IP_ADDR1  = 16,
        .WIRELESS_IP_ADDR2  = 109,
        .WIRELESS_IP_ADDR3  = 152,

        .WIRELESS_NETMASK0  = 255,
        .WIRELESS_NETMASK1  = 255,
        .WIRELESS_NETMASK2  = 255,
        .WIRELESS_NETMASK3  = 0,

        .WIRELESS_GATEWAY0  = 172,
        .WIRELESS_GATEWAY1  = 16,
        .WIRELESS_GATEWAY2  = 109,
        .WIRELESS_GATEWAY3  = 254,

        .SERVER_IPADDR1  = 192,
        .SERVER_IPADDR2  = 168,
        .SERVER_IPADDR3  = 1,
        .SERVER_IPADDR4  = 1,

        .CLIENT_IPADDR1  = 192,
        .CLIENT_IPADDR2  = 168,
        .CLIENT_IPADDR3  = 1,
        .CLIENT_IPADDR4  = 2,

        .SUB_NET_MASK1   = 255,
        .SUB_NET_MASK2   = 255,
        .SUB_NET_MASK3   = 255,
        .SUB_NET_MASK4   = 0,
    };

    dev_ioctl(device, IOCTL_ETH_SET_LAN_SETTING, (u32)&lan_setting_info);
}

static void eth_net_task(void *arg)
{
    char mac_addr[6] = {0x9c, 0x37, 0xf4, 0x0e, 0x4d, 0xc9};

    while (1) {
        void *dev = dev_open("eth", NULL);
        if (!dev) {
            return;
        }

        dev_ioctl(dev, IOCTL_ETH_SET_MAC_ADDR, (int)mac_addr);

        eth_set_lan_setting_info(dev);

        dev_ioctl(dev, IOCTL_ETH_EVENT_CB_FUNC, (u32)eth_state_cb);

        dev_ioctl(dev, IOCTL_ETH_NETWORK_START, 0);

        os_time_dly(6000);

        dev_ioctl(dev, IOCTL_ETH_NETWORK_STOP, 0);

        dev_close(dev);

        os_time_dly(500);
    }
}

static int wire_net_init(void)//主要是有线网卡线程的
{
    return thread_fork("eth_net_task", 10, 512, 0, 0, eth_net_task, NULL);
}
late_initcall(wire_net_init);

#include "sock_api/sock_api.h"

static void ping_cb(void *priv, u32 cnt, u32 time)
{
    printf("%s, cnt = %d, time = %d", __FUNCTION__, cnt, time);
}

static void dns_found(const char *name, const ip_addr_t *ipaddr, void *callback_arg)
{
    printf("%s, name = %s, ip = %s", __func__, name, ipaddr_ntoa(ipaddr));
}

static void udp_task(void *priv)
{
    void *socket_fd;
    int recv_len;
    u8 recv_buf[50] = {0};
    struct sockaddr_in local_addr = {0};
    struct sockaddr_in remote_addr = {0};
    socklen_t len = sizeof(remote_addr);

    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(39766);

    if (!(socket_fd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL))) {
        printf("%s build socket fail",  __FILE__);
        return;
    }

    if (sock_bind(socket_fd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr))) {
        printf("%s sock_bind fail", __FILE__);
        return;
    }

    for (;;) {
        if ((recv_len = sock_recvfrom(socket_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&remote_addr, &len)) > 0) {
            printf("recv_len is %d, %s", recv_len, recv_buf);
            sock_sendto(socket_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr_in));
        }
    }
}

static void udp_tx_task(void *priv)
{
    u32 opt = 1;
    void *tx_fd;
    struct sockaddr_in dest;
    char buf[] = "jlkjdfljaslfjlasjf";

    tx_fd = sock_reg(AF_INET, SOCK_DGRAM, 0, NULL, NULL);
    if (tx_fd == NULL) {
        printf("udp sock_reg fail.");
        return;
    }
    sock_setsockopt(tx_fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    dest.sin_family = AF_INET;
    //dest.sin_addr.s_addr = inet_addr("255.255.255.255");
    dest.sin_addr.s_addr = inet_addr("172.16.109.88");
    dest.sin_port = htons(39766);

    for (;;) {
        if (tx_fd) {
            sock_sendto(tx_fd, buf, strlen(buf), 0, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
        }
        os_time_dly(100);
        putchar('T');
    }
}

static void eth_network_test(void)
{
    static u8 init = 0;

    if (!init) {
        init = 1;
    } else {
        return;
    }
    //ping_init("120.24.247.138", 1000, 20, ping_cb, NULL);
    //ping_init("172.16.1.254", 1000, 20, ping_cb, NULL);

    //ip_addr_t host_ip;
    //dns_gethostbyname("www.taobao.com", &host_ip, dns_found, NULL);

    thread_fork("udp_task", 30, 512, 0, NULL, udp_task, NULL);
    //thread_fork("udp_tx_task", 10, 512, 0, NULL, udp_tx_task, NULL);
}

#endif
