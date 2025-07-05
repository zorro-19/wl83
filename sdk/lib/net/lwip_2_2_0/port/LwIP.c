
#define __LW_IP_C


/* #include "system/includes.h" */
#include "stdlib.h"


/* Includes ------------------------------------------------------------------*/

#include "lwip/inet.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/dhcp6.h"
#include "lwip/prot/dhcp.h"
#include "lwip/autoip.h"
#include "lwip/dns.h"
#include "lwip/etharp.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "lwip.h"
#include "lwip/sys.h"
#include "printf.h"
#include "sys_arch.h"
/* #include "eth/eth_phy.h" */
#include "wifi/wifi_connect.h"

#define HAVE_ETH_WIRE_NETIF
#define HAVE_LTE_NETIF
#define HAVE_BT_NETIF
#define HAVE_EXT_WIRELESS_NETIF
#define HAVE_WRIELESS_RAW_NETIF

extern const u8 IPV4_ADDR_CONFLICT_DETECT;
extern char *itoa(int num, char *str, int radix);
extern err_t wireless_ethernetif_init(struct netif *netif);
extern err_t ext_wireless_ethernetif_init(struct netif *netif);
extern err_t wired_ethernetif_init(struct netif *netif);
extern err_t bt_ethernetif_init(struct netif *netif);
extern err_t lte_ethernetif_init(struct netif *netif);
extern err_t wireless_raw_ethernetif_init(struct netif *netif);
extern void ntp_client_get_time(const char *host);
extern int netdev_get_mac_addr(u8 *mac_addr);
static void __lwip_renew(unsigned short parm);

int __attribute__((weak)) lwip_event_cb(void *lwip_ctx, enum LWIP_EVENT event)
{
    return 0;
}

int __attribute__((weak)) lte_lwip_event_cb(void *lwip_ctx, enum LWIP_EVENT event)
{
    return 0;
}

int __attribute__((weak)) ext_lwip_event_cb(void *lwip_ctx, enum LWIP_EVENT event)
{
    return 0;
}

int __attribute__((weak)) eth_lwip_event_cb(void *lwip_ctx, enum LWIP_EVENT event)
{
    return 0;
}

int __attribute__((weak)) bt_lwip_event_cb(void *lwip_ctx, enum LWIP_EVENT event)
{
    return 0;
}

void __attribute__((weak)) dns_set_server(unsigned int *dnsserver)
{
    *dnsserver = 0x23415679;
}

int __attribute__((weak)) socket_send_but_netif_busy_hook(int s, char type_udp)
{
    return 0;
}

static struct lan_setting wireless_lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 1,
    .WIRELESS_IP_ADDR3  = 1,

    .WIRELESS_NETMASK0  = 255,
    .WIRELESS_NETMASK1  = 255,
    .WIRELESS_NETMASK2  = 255,
    .WIRELESS_NETMASK3  = 0,

    .WIRELESS_GATEWAY0  = 192,
    .WIRELESS_GATEWAY1  = 168,
    .WIRELESS_GATEWAY2  = 1,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 1,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 1,
    .CLIENT_IPADDR4  = 101,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};

#ifdef HAVE_WRIELESS_RAW_NETIF
static struct lan_setting wireless_raw_lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 1,
    .WIRELESS_IP_ADDR3  = 1,

    .WIRELESS_NETMASK0  = 255,
    .WIRELESS_NETMASK1  = 255,
    .WIRELESS_NETMASK2  = 255,
    .WIRELESS_NETMASK3  = 0,

    .WIRELESS_GATEWAY0  = 192,
    .WIRELESS_GATEWAY1  = 168,
    .WIRELESS_GATEWAY2  = 1,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 1,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 1,
    .CLIENT_IPADDR4  = 101,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};
#endif


#ifdef HAVE_WRIELESS_RAW_NETIF
static struct netif wireless_raw_netif;
#endif
static struct netif wireless_netif;
static u32 wireless_dhcp_timeout_cnt;
static u8 lwip_static_ip_renew[MAX_NETIF_NUM];

#ifdef HAVE_EXT_WIRELESS_NETIF
static struct lan_setting ext_wireless_lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 0,
    .WIRELESS_IP_ADDR3  = 1,

    .WIRELESS_NETMASK0  = 255,
    .WIRELESS_NETMASK1  = 255,
    .WIRELESS_NETMASK2  = 255,
    .WIRELESS_NETMASK3  = 0,

    .WIRELESS_GATEWAY0  = 192,
    .WIRELESS_GATEWAY1  = 168,
    .WIRELESS_GATEWAY2  = 0,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 0,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 0,
    .CLIENT_IPADDR4  = 101,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};

static struct netif ext_wireless_netif;
static u32 ext_wireless_dhcp_timeout_cnt;
#endif

#ifdef HAVE_LTE_NETIF
static struct lan_setting lte_lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 0,
    .WIRELESS_IP_ADDR3  = 1,

    .WIRELESS_NETMASK0  = 255,
    .WIRELESS_NETMASK1  = 255,
    .WIRELESS_NETMASK2  = 255,
    .WIRELESS_NETMASK3  = 0,

    .WIRELESS_GATEWAY0  = 192,
    .WIRELESS_GATEWAY1  = 168,
    .WIRELESS_GATEWAY2  = 0,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 0,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 0,
    .CLIENT_IPADDR4  = 101,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};

static struct netif lte_netif;
static u32 lte_dhcp_timeout_cnt;
#endif

#ifdef HAVE_ETH_WIRE_NETIF
static struct lan_setting eth_lan_setting_info = {
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
    .SERVER_IPADDR3  = 0,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 0,
    .CLIENT_IPADDR4  = 101,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};

static struct netif wire_netif;
static u8 use_dhcp = 1;
static u32 wire_dhcp_timeout_cnt;
#endif

#ifdef HAVE_BT_NETIF
static struct lan_setting bt_lan_setting_info = {
    .WIRELESS_IP_ADDR0  = 192,
    .WIRELESS_IP_ADDR1  = 168,
    .WIRELESS_IP_ADDR2  = 0,
    .WIRELESS_IP_ADDR3  = 1,

    .WIRELESS_NETMASK0  = 255,
    .WIRELESS_NETMASK1  = 255,
    .WIRELESS_NETMASK2  = 255,
    .WIRELESS_NETMASK3  = 0,

    .WIRELESS_GATEWAY0  = 192,
    .WIRELESS_GATEWAY1  = 168,
    .WIRELESS_GATEWAY2  = 0,
    .WIRELESS_GATEWAY3  = 1,

    .SERVER_IPADDR1  = 192,
    .SERVER_IPADDR2  = 168,
    .SERVER_IPADDR3  = 0,
    .SERVER_IPADDR4  = 1,

    .CLIENT_IPADDR1  = 192,
    .CLIENT_IPADDR2  = 168,
    .CLIENT_IPADDR3  = 0,
    .CLIENT_IPADDR4  = 101,

    .SUB_NET_MASK1   = 255,
    .SUB_NET_MASK2   = 255,
    .SUB_NET_MASK3   = 255,
    .SUB_NET_MASK4   = 0,
};

static struct netif bt_netif;
static u32 bt_dhcp_timeout_cnt;
#endif

#define DHCP_TMR_INTERVAL 100  //mill_sec
static int dhcp_timeout_msec = 15 * 1000;
static u8 get_time_init;
extern const u8 ntp_get_time_init;

struct lan_setting *net_get_lan_info(u8_t lwip_netif)
{
    if (lwip_netif == WIFI_NETIF) {
        return &wireless_lan_setting_info;
    }

#ifdef HAVE_WRIELESS_RAW_NETIF
    if (lwip_netif == WIFI_RAW_NETIF) {
        return &wireless_raw_lan_setting_info;
    }
#endif

#ifdef HAVE_EXT_WIRELESS_NETIF
    else if (lwip_netif == EXT_WIFI_NETIF) {
        return &ext_wireless_lan_setting_info;
    }
#endif
#ifdef HAVE_LTE_NETIF
    else if (lwip_netif == LTE_NETIF) {
        return &lte_lan_setting_info;
    }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
    else if (lwip_netif == ETH_NETIF) {
        return &eth_lan_setting_info;
    }
#endif
#ifdef HAVE_BT_NETIF
    else if (lwip_netif == BT_NETIF) {
        return &bt_lan_setting_info;
    }
#endif

    return NULL;
}

struct netif *net_get_netif_handle(u8_t lwip_netif)
{
    if (lwip_netif == WIFI_NETIF) {
        return &wireless_netif;
    }

#ifdef HAVE_WRIELESS_RAW_NETIF
    if (lwip_netif == WIFI_RAW_NETIF) {
        return &wireless_raw_netif;
    }
#endif

#ifdef HAVE_EXT_WIRELESS_NETIF
    else if (lwip_netif == EXT_WIFI_NETIF) {
        return &ext_wireless_netif;
    }
#endif
#ifdef HAVE_LTE_NETIF
    else if (lwip_netif == LTE_NETIF) {
        return &lte_netif;
    }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
    else if (lwip_netif == ETH_NETIF) {
        return &wire_netif;
    }
#endif
#ifdef HAVE_BT_NETIF
    else if (lwip_netif == BT_NETIF) {
        return &bt_netif;
    }
#endif

    return NULL;
}

int net_set_lan_info(struct lan_setting *__lan_setting_info)
{
    struct lan_setting *lan_setting_info = net_get_lan_info(WIFI_NETIF);
    if (!lan_setting_info) {
        return -1;
    }

    lan_setting_info->WIRELESS_IP_ADDR0  = __lan_setting_info->WIRELESS_IP_ADDR0;
    lan_setting_info->WIRELESS_IP_ADDR1  = __lan_setting_info->WIRELESS_IP_ADDR1;
    lan_setting_info->WIRELESS_IP_ADDR2  = __lan_setting_info->WIRELESS_IP_ADDR2;
    lan_setting_info->WIRELESS_IP_ADDR3  = __lan_setting_info->WIRELESS_IP_ADDR3;

    lan_setting_info->WIRELESS_NETMASK0  = __lan_setting_info->WIRELESS_NETMASK0;
    lan_setting_info->WIRELESS_NETMASK1  = __lan_setting_info->WIRELESS_NETMASK1;
    lan_setting_info->WIRELESS_NETMASK2  = __lan_setting_info->WIRELESS_NETMASK2;
    lan_setting_info->WIRELESS_NETMASK3  = __lan_setting_info->WIRELESS_NETMASK3;

    lan_setting_info->WIRELESS_GATEWAY0  = __lan_setting_info->WIRELESS_GATEWAY0;
    lan_setting_info->WIRELESS_GATEWAY1  = __lan_setting_info->WIRELESS_GATEWAY1;
    lan_setting_info->WIRELESS_GATEWAY2  = __lan_setting_info->WIRELESS_GATEWAY2;
    lan_setting_info->WIRELESS_GATEWAY3  = __lan_setting_info->WIRELESS_GATEWAY3;

    lan_setting_info->SERVER_IPADDR1     = __lan_setting_info->SERVER_IPADDR1;
    lan_setting_info->SERVER_IPADDR2     = __lan_setting_info->SERVER_IPADDR2;
    lan_setting_info->SERVER_IPADDR3     = __lan_setting_info->SERVER_IPADDR3;
    lan_setting_info->SERVER_IPADDR4     = __lan_setting_info->SERVER_IPADDR4;

    lan_setting_info->CLIENT_IPADDR1     = __lan_setting_info->CLIENT_IPADDR1;
    lan_setting_info->CLIENT_IPADDR2     = __lan_setting_info->CLIENT_IPADDR2;
    lan_setting_info->CLIENT_IPADDR3     = __lan_setting_info->CLIENT_IPADDR3;
    lan_setting_info->CLIENT_IPADDR4     = __lan_setting_info->CLIENT_IPADDR4;

    lan_setting_info->SUB_NET_MASK1      = __lan_setting_info->SUB_NET_MASK1;
    lan_setting_info->SUB_NET_MASK2      = __lan_setting_info->SUB_NET_MASK2;
    lan_setting_info->SUB_NET_MASK3      = __lan_setting_info->SUB_NET_MASK3;
    lan_setting_info->SUB_NET_MASK4      = __lan_setting_info->SUB_NET_MASK4;

    return 0;
}

int net_set_lan_info_ext(struct lan_setting *__lan_setting_info, u8_t lwip_netif)
{
    struct lan_setting *lan_setting_info = net_get_lan_info(lwip_netif);
    if (!lan_setting_info) {
        return -1;
    }

    lan_setting_info->WIRELESS_IP_ADDR0  = __lan_setting_info->WIRELESS_IP_ADDR0;
    lan_setting_info->WIRELESS_IP_ADDR1  = __lan_setting_info->WIRELESS_IP_ADDR1;
    lan_setting_info->WIRELESS_IP_ADDR2  = __lan_setting_info->WIRELESS_IP_ADDR2;
    lan_setting_info->WIRELESS_IP_ADDR3  = __lan_setting_info->WIRELESS_IP_ADDR3;

    lan_setting_info->WIRELESS_NETMASK0  = __lan_setting_info->WIRELESS_NETMASK0;
    lan_setting_info->WIRELESS_NETMASK1  = __lan_setting_info->WIRELESS_NETMASK1;
    lan_setting_info->WIRELESS_NETMASK2  = __lan_setting_info->WIRELESS_NETMASK2;
    lan_setting_info->WIRELESS_NETMASK3  = __lan_setting_info->WIRELESS_NETMASK3;

    lan_setting_info->WIRELESS_GATEWAY0  = __lan_setting_info->WIRELESS_GATEWAY0;
    lan_setting_info->WIRELESS_GATEWAY1  = __lan_setting_info->WIRELESS_GATEWAY1;
    lan_setting_info->WIRELESS_GATEWAY2  = __lan_setting_info->WIRELESS_GATEWAY2;
    lan_setting_info->WIRELESS_GATEWAY3  = __lan_setting_info->WIRELESS_GATEWAY3;

    lan_setting_info->SERVER_IPADDR1     = __lan_setting_info->SERVER_IPADDR1;
    lan_setting_info->SERVER_IPADDR2     = __lan_setting_info->SERVER_IPADDR2;
    lan_setting_info->SERVER_IPADDR3     = __lan_setting_info->SERVER_IPADDR3;
    lan_setting_info->SERVER_IPADDR4     = __lan_setting_info->SERVER_IPADDR4;

    lan_setting_info->CLIENT_IPADDR1     = __lan_setting_info->CLIENT_IPADDR1;
    lan_setting_info->CLIENT_IPADDR2     = __lan_setting_info->CLIENT_IPADDR2;
    lan_setting_info->CLIENT_IPADDR3     = __lan_setting_info->CLIENT_IPADDR3;
    lan_setting_info->CLIENT_IPADDR4     = __lan_setting_info->CLIENT_IPADDR4;

    lan_setting_info->SUB_NET_MASK1      = __lan_setting_info->SUB_NET_MASK1;
    lan_setting_info->SUB_NET_MASK2      = __lan_setting_info->SUB_NET_MASK2;
    lan_setting_info->SUB_NET_MASK3      = __lan_setting_info->SUB_NET_MASK3;
    lan_setting_info->SUB_NET_MASK4      = __lan_setting_info->SUB_NET_MASK4;

    return 0;
}

#if LWIP_IPV6
const char *ipv6_addr_types_to_str[6] = {
    "IP6_ADDR_IS_UNKNOWN",
    "IP6_ADDR_IS_GLOBAL",
    "IP6_ADDR_IS_LINK_LOCAL",
    "IP6_ADDR_IS_SITE_LOCAL",
    "IP6_ADDR_IS_UNIQUE_LOCAL",
    "IP6_ADDR_IS_IPV4_MAPPED_IPV6"
};

ip6_addr_type get_ip6_addr_type(ip6_addr_t *ip6_addr)
{
    if (ip6_addr_isglobal(ip6_addr)) {
        return IP6_ADDR_IS_GLOBAL;
    } else if (ip6_addr_islinklocal(ip6_addr)) {
        return IP6_ADDR_IS_LINK_LOCAL;
    } else if (ip6_addr_issitelocal(ip6_addr)) {
        return IP6_ADDR_IS_SITE_LOCAL;
    } else if (ip6_addr_isuniquelocal(ip6_addr)) {
        return IP6_ADDR_IS_UNIQUE_LOCAL;
    } else if (ip6_addr_isipv4mappedipv6(ip6_addr)) {
        return IP6_ADDR_IS_IPV4_MAPPED_IPV6;
    }
    return IP6_ADDR_IS_UNKNOWN;
}
#endif

/**
 * @brief Display_IPAddress Display IP Address
 *
 */
void Display_IPAddress(void)
{
    struct netif *netif = netif_list;

    while (netif != NULL) {
        printf("Default network interface: %c%c\n", netif->name[0], netif->name[1]);
        printf("ip4 address: %s\n", inet_ntoa(*((ip4_addr_t *) & (netif->ip_addr))));
        printf("gw address: %s\n", inet_ntoa(*((ip4_addr_t *) & (netif->gw))));
        printf("net mask  : %s\n\n", inet_ntoa(*((ip4_addr_t *) & (netif->netmask))));

#if LWIP_IPV6
        for (int i = 0; i < LWIP_IPV6_NUM_ADDRESSES; i++) {
            char *ip6_addr_state;
            if (ip6_addr_isinvalid(netif->ip6_addr_state[i])) {
                ip6_addr_state = "INVALID";
            } else if (ip6_addr_istentative(netif->ip6_addr_state[i])) {
                ip6_addr_state = "TENTATIVE";
            } else if (ip6_addr_isvalid(netif->ip6_addr_state[i])) {
                ip6_addr_state = "VALID";
            } else if (ip6_addr_ispreferred(netif->ip6_addr_state[i])) {
                ip6_addr_state = "PREFERRED";
            } else if (ip6_addr_isdeprecated(netif->ip6_addr_state[i])) {
                ip6_addr_state = "DEPRECATED";
            } else if (ip6_addr_isduplicated(netif->ip6_addr_state[i])) {
                ip6_addr_state = "DUPLICATE";
            } else {
                ip6_addr_state = "UNKNOW";
            }

            if (strcmp(ip6addr_ntoa(&netif->ip6_addr[i].u_addr.ip6), "::"))
                printf("ip6 address: %s, type = %s\n",
                       ip6addr_ntoa(&netif->ip6_addr[i].u_addr.ip6), ipv6_addr_types_to_str[get_ip6_addr_type(&netif->ip6_addr[i])]);
        }
#endif
        netif = netif->next;
    }
}

void lwip_set_dhcp_timeout(int sec)
{
    dhcp_timeout_msec = sec * 1000;
}

static void network_is_dhcp_bound(struct netif *netif)
{
    u32 *p_to = NULL;
    struct dhcp *dhcp = ((struct dhcp *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP));

    if (netif == &wireless_netif) {
        p_to = &wireless_dhcp_timeout_cnt;
    }
#ifdef HAVE_EXT_WIRELESS_NETIF
    if (netif == &ext_wireless_netif) {
        p_to = &ext_wireless_dhcp_timeout_cnt;
    }
#endif
#ifdef HAVE_LTE_NETIF
    else if (netif == &lte_netif) {
        p_to = &lte_dhcp_timeout_cnt;
    }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
    else if (netif == &wire_netif) {
        p_to = &wire_dhcp_timeout_cnt;
    }
#endif
#ifdef HAVE_BT_NETIF
    else if (netif == &bt_netif) {
        p_to = &bt_dhcp_timeout_cnt;
    }
#endif

    if ((++(*p_to))*DHCP_TMR_INTERVAL >  dhcp_timeout_msec) {
        (*p_to) = 0;

        unsigned int parm = WIFI_NETIF;

        if (netif == &wireless_netif) {
            lwip_event_cb(NULL, LWIP_WIRELESS_DHCP_BOUND_TIMEOUT);
            parm = WIFI_NETIF;
        }
#ifdef HAVE_EXT_WIRELESS_NETIF
        else if (netif == &ext_wireless_netif) {
            ext_lwip_event_cb(NULL, LWIP_EXT_WIRELESS_DHCP_BOUND_TIMEOUT);
            parm = EXT_WIFI_NETIF;
        }
#endif
#ifdef HAVE_LTE_NETIF
        else if (netif == &lte_netif) {
            lte_lwip_event_cb(NULL, LWIP_LTE_DHCP_BOUND_TIMEOUT);
            parm = LTE_NETIF;
        }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
        else if (netif == &wire_netif) {
            eth_lwip_event_cb(NULL, LWIP_LTE_DHCP_BOUND_TIMEOUT);
            parm = ETH_NETIF;
        }
#endif
#ifdef HAVE_BT_NETIF
        else if (netif == &bt_netif) {
            bt_lwip_event_cb(NULL, LWIP_BT_DHCP_BOUND_TIMEOUT);
            parm = BT_NETIF;
        }
#endif

#if 1
        parm <<= 8;
        parm |= 1;
        __lwip_renew(parm);
#else
        tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, netif);//减缓network_is_dhcp_bound 刚好被lwip_renew装载的情况
        if (tcpip_timeout(DHCP_TMR_INTERVAL, (sys_timeout_handler)network_is_dhcp_bound, netif) != ERR_OK) {
            LWIP_ASSERT("failed to create timeout network_is_dhcp_bound", 0);
        }
#endif
    } else {
        if (dhcp->state == DHCP_STATE_BOUND) {
            (*p_to) = 0;
            Display_IPAddress();

#if DNS_LOCAL_HOSTLIST
            if (netif == &wireless_netif) {
                dns_local_removehost(LOCAL_WIRELESS_HOST_NAME, &wireless_netif.ip_addr);

                if (dns_local_addhost(LOCAL_WIRELESS_HOST_NAME, &wireless_netif.ip_addr) != ERR_OK) {
                    puts("dns_local_addhost err`.\n");
                }
            }
#ifdef HAVE_EXT_WIRELESS_NETIF
            else if (netif == &ext_wireless_netif) {
                dns_local_removehost(LOCAL_EXT_WIRELESS_HOST_NAME, &ext_wireless_netif.ip_addr);

                if (dns_local_addhost(LOCAL_EXT_WIRELESS_HOST_NAME, &ext_wireless_netif.ip_addr) != ERR_OK) {
                    puts("dns_local_addhost err`.\n");
                }
            }
#endif
#ifdef HAVE_LTE_NETIF
            else if (netif == &lte_netif) {
                dns_local_removehost(LOCAL_LTE_HOST_NAME, &lte_netif.ip_addr);

                if (dns_local_addhost(LOCAL_LTE_HOST_NAME, &lte_netif.ip_addr) != ERR_OK) {
                    puts("dns_local_addhost err`.\n");
                }
            }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
            else if (netif == &wire_netif) {
                dns_local_removehost(LOCAL_WIRE_HOST_NAME, &wire_netif.ip_addr);

                if (dns_local_addhost(LOCAL_WIRE_HOST_NAME, &wire_netif.ip_addr) != ERR_OK) {
                    puts("dns_local_addhost err`.\n");
                }
            }
#endif
#ifdef HAVE_BT_NETIF
            else if (netif == &bt_netif) {
                dns_local_removehost(LOCAL_BT_HOST_NAME, &bt_netif.ip_addr);

                if (dns_local_addhost(LOCAL_BT_HOST_NAME, &bt_netif.ip_addr) != ERR_OK) {
                    puts("dns_local_addhost err`.\n");
                }
            }
#endif
#endif
            if (netif == &wireless_netif) {
                lwip_event_cb(NULL, LWIP_WIRELESS_DHCP_BOUND_SUCC);
            }

#ifdef HAVE_EXT_WIRELESS_NETIF
            else if (netif == &ext_wireless_netif) {
                ext_lwip_event_cb(NULL, LWIP_EXT_WIRELESS_DHCP_BOUND_SUCC);
            }
#endif
#ifdef HAVE_LTE_NETIF
            else if (netif == &lte_netif) {
                lte_lwip_event_cb(NULL, LWIP_LTE_DHCP_BOUND_SUCC);
            }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
            else if (netif == &wire_netif) {
                eth_lwip_event_cb(NULL, LWIP_WIRE_DHCP_BOUND_SUCC);
            }
#endif
#ifdef HAVE_BT_NETIF
            else if (netif == &bt_netif) {
                bt_lwip_event_cb(NULL, LWIP_BT_DHCP_BOUND_SUCC);
            }
#endif
            if (ntp_get_time_init && !get_time_init) {
                get_time_init = 1;
                thread_fork("ntp_client_get_time", 10, 1024, 0, 0, (void (*)(void *))ntp_client_get_time, NULL);
            }
        } else {
            tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, netif);//减缓network_is_dhcp_bound 刚好被lwip_renew装载的情况
            if (tcpip_timeout(DHCP_TMR_INTERVAL, (sys_timeout_handler)network_is_dhcp_bound, netif) != ERR_OK) {
                LWIP_ASSERT("failed to create timeout network_is_dhcp_bound", 0);
            }
        }
    }
}

/**
 * @brief Get_IPAddress
 *
 */
void Get_IPAddress(u8_t lwip_netif, char *ipaddr)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

    inet_ntoa_r(*((ip4_addr_t *) & (netif->ip_addr)), ipaddr, IP4ADDR_STRLEN_MAX);
}

void get_gateway(u8_t lwip_netif, char *ipaddr)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

    inet_ntoa_r(*((ip4_addr_t *) & (netif->gw)), ipaddr, IP4ADDR_STRLEN_MAX);
}

int get_netif_macaddr_and_ipaddr(ip4_addr_t *ipaddr, unsigned char *mac_addr, int count)
{
    struct netif *netif = netif_list;
    int i;
    unsigned char (*hwaddr)[6] = (unsigned char (*)[6])mac_addr;
    int p_ipaddr;

    for (i = 0; i < count && netif != NULL; i++, netif = netif->next) {
        memcpy(ipaddr, &netif->ip_addr, sizeof(ip4_addr_t));
        memcpy(hwaddr, netif->hwaddr, NETIF_MAX_HWADDR_LEN);
        p_ipaddr = ipaddr->addr;
        printf("|get_netif_macaddr_and_ipaddr-> [0x%x],[%x%x%x%x%x%x]\n",
               p_ipaddr, netif->hwaddr[0], netif->hwaddr[1], netif->hwaddr[2], netif->hwaddr[3], netif->hwaddr[4], netif->hwaddr[5]);

        ++ipaddr;
        ++hwaddr;
    }

    return i;
}

void set_wireless_netif_macaddr(const char *mac_addr)
{
    memcpy(wireless_netif.hwaddr, mac_addr, NETIF_MAX_HWADDR_LEN);
}

#if LWIP_NETIF_EXT_STATUS_CALLBACK
static netif_ext_callback_t netif_callback = { .callback_fn = NULL, .next = NULL };
static void netif_callback_fn(struct netif *netif, netif_nsc_reason_t reason, const netif_ext_callback_args_t *args)
{
#if LWIP_IPV6
    if ((reason & LWIP_NSC_IPV6_ADDR_STATE_CHANGED) && (args != NULL)) {
        s8_t addr_idx = args->ipv6_addr_state_changed.addr_index;

        //if (netif_ip6_addr_state(netif, addr_idx) & IP6_ADDR_VALID)  {
        if (netif_ip6_addr_state(netif, addr_idx) & IP6_ADDR_PREFERRED)  {
            if (!ip6_addr_islinklocal(netif_ip6_addr(netif, addr_idx))\
                && !ip6_addr_isany(netif_ip6_addr(netif, addr_idx))) {
                printf("got ipv6[idx:%d]: %s\n", addr_idx, ip6addr_ntoa(netif_ip_addr6(netif, addr_idx)));
                lwip_event_cb(NULL, LWIP_IP_GOT_IPV6_SUCC);
            }
        }
    }
#endif /* #if LWIP_IPV6 */
}
#endif

static void nd6_netif_cache_cleanup(struct netif *netif)
{
#if LWIP_IPV6
    for (int i = 0; i < LWIP_IPV6_NUM_ADDRESSES; i++) {
        /* if (!ip6_addr_islinklocal(netif_ip6_addr(netif, i))) */
        /* { */
        ip_addr_set_zero_ip6(&netif->ip6_addr[i]);
        netif->ip6_addr_state[i] = IP6_ADDR_INVALID;
#if LWIP_IPV6_ADDRESS_LIFETIMES
        netif->ip6_addr_valid_life[i] = IP6_ADDR_LIFE_STATIC;
        netif->ip6_addr_pref_life[i] = IP6_ADDR_LIFE_STATIC;
#endif /* LWIP_IPV6_ADDRESS_LIFETIMES */
        /* } */
    }

    nd6_cleanup_netif(netif);
    nd6_restart_netif(netif);
#endif
}

void nd6_renew(struct netif *netif)
{
    nd6_netif_cache_cleanup(netif);
    nd6_cleanup_netif(netif);
    nd6_restart_netif(netif);

    netif_create_ip6_linklocal_address(netif, 1);

#if LWIP_IPV6_DHCP6
#if LWIP_IPV6_DHCP6_STATEFUL
    //如果stateful使能需要先disable掉，再重新使能, 同时需要重新创建linklocal地址
    dhcp6_disable_stateful(netif);
    /* netif_create_ip6_linklocal_address(netif, 1); */

    if (tcpip_callback((tcpip_callback_fn)dhcp6_enable_stateful, netif) != ERR_OK) {
        LWIP_ASSERT("failed to create timeout dhcp6_enable_stateful", 0);
    }
#else
    /* netif_create_ip6_linklocal_address(netif, 1); */
    if (tcpip_callback((tcpip_callback_fn)dhcp6_enable_stateless, netif) != ERR_OK) {
        LWIP_ASSERT("failed to create timeout dhcp6_enable_stateless", 0);
    }
#endif
#endif
}

static void dhcp_renew_ipaddr(struct netif *netif)
{

    ip_addr_set_zero(&netif->ip_addr);
    ip_addr_set_zero(&netif->netmask);
    ip_addr_set_zero(&netif->gw);


    //dhcp发送和接收需要放在同一线程里做
    if (tcpip_callback((tcpip_callback_fn)dhcp_start, netif) != ERR_OK) {
        LWIP_ASSERT("failed to create timeout dhcp_start", 0);
    }

#if 0
    if (tcpip_callback((tcpip_callback_fn)dhcp_network_changed, netif) != ERR_OK) {
        LWIP_ASSERT("failed to create timeout dhcp_network_changed", 0);
    }
#endif
}

/**
 * @brief TcpipInitDone wait for tcpip init being done
 *
 * @param arg the semaphore to be signaled
 */
static void TcpipInitDone(void *arg)
{
    sys_sem_t *sem;

    sem = arg;
    sys_sem_signal(sem);
}

void lwip_set_default_netif(u8_t lwip_netif)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

    netif_set_default(netif);
}

void lwip_netif_remove(u8_t lwip_netif)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

    struct lan_setting *lan_setting_info = net_get_lan_info(lwip_netif);
    if (!lan_setting_info) {
        return;
    }

#ifdef HAVE_LTE_NETIF
    struct ip4_addr ipaddr;

    if (lwip_netif == LTE_NETIF) {
        dhcp_cleanup(netif);
        IP4_ADDR(&ipaddr, lan_setting_info->WIRELESS_IP_ADDR0, lan_setting_info->WIRELESS_IP_ADDR1, lan_setting_info->WIRELESS_IP_ADDR2, lan_setting_info->WIRELESS_IP_ADDR3);
        dns_local_removehost(LOCAL_LTE_HOST_NAME, &ipaddr);
        dns_local_removehost(LOCAL_LTE_HOST_NAME, &netif->ip_addr);
    }
#endif

    netif_remove(netif);
}

void lwip_netif_set_up(u8_t lwip_netif)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

    netif_set_up(netif);
}

void lwip_netif_set_down(u8_t lwip_netif)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

    struct lan_setting *lan_setting_info = net_get_lan_info(lwip_netif);
    if (!lan_setting_info) {
        return;
    }

#ifdef HAVE_LTE_NETIF
    struct ip4_addr ipaddr;

    if (lwip_netif == LTE_NETIF) {
        /* dhcp_cleanup(netif); */
        IP4_ADDR(&ipaddr, lan_setting_info->WIRELESS_IP_ADDR0, lan_setting_info->WIRELESS_IP_ADDR1, lan_setting_info->WIRELESS_IP_ADDR2, lan_setting_info->WIRELESS_IP_ADDR3);
        dns_local_removehost(LOCAL_LTE_HOST_NAME, &ipaddr);
        dns_local_removehost(LOCAL_LTE_HOST_NAME, &netif->ip_addr);
    }
#endif

    netif_set_down(netif);
}

static void __lwip_renew(unsigned short parm)
{
    struct ip4_addr ipaddr;
    struct ip4_addr netmask;
    struct ip4_addr gw;
    u8_t lwip_netif = parm >> 8;
    u8_t dhcp = (u8_t)parm;

    printf("|lwip_renew [%d][%d].\n", lwip_netif, dhcp);

    struct lan_setting *lan_setting_info = net_get_lan_info(lwip_netif);
    if (!lan_setting_info) {
        return;
    }

    if (lwip_netif == WIFI_NETIF) {
        int wifi_get_mac(u8 * mac);
        wifi_get_mac(wireless_netif.hwaddr);

#if LWIP_NETIF_EXT_STATUS_CALLBACK
        netif_remove_ext_callback(&netif_callback);
        netif_add_ext_callback(&netif_callback, netif_callback_fn);
#endif

#if LWIP_IPV6
        nd6_renew(&wireless_netif);
#endif

        if (dhcp) {

            dhcp_renew_ipaddr(&wireless_netif);

            tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, &wireless_netif);

            wireless_dhcp_timeout_cnt = 0;

            if (tcpip_timeout(DHCP_TMR_INTERVAL, (sys_timeout_handler)network_is_dhcp_bound, &wireless_netif) != ERR_OK) {
                LWIP_ASSERT("failed to create timeout network_is_dhcp_bound", 0);
            }
        } else {
            tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, &wireless_netif);
            IP4_ADDR(&ipaddr, lan_setting_info->WIRELESS_IP_ADDR0, lan_setting_info->WIRELESS_IP_ADDR1, lan_setting_info->WIRELESS_IP_ADDR2, lan_setting_info->WIRELESS_IP_ADDR3);
            IP4_ADDR(&netmask, lan_setting_info->WIRELESS_NETMASK0, lan_setting_info->WIRELESS_NETMASK1, lan_setting_info->WIRELESS_NETMASK2, lan_setting_info->WIRELESS_NETMASK3);
            IP4_ADDR(&gw, lan_setting_info->WIRELESS_GATEWAY0, lan_setting_info->WIRELESS_GATEWAY1, lan_setting_info->WIRELESS_GATEWAY2, lan_setting_info->WIRELESS_GATEWAY3);
            netif_set_addr(&wireless_netif, &ipaddr, &netmask, &gw);

            lwip_event_cb(NULL, LWIP_WIRELESS_DHCP_BOUND_SUCC);
            Display_IPAddress();

            if (IPV4_ADDR_CONFLICT_DETECT) {
                if ((etharp_request(&wireless_netif, &ipaddr)) != ERR_OK) {
                    printf("etharp_request failed!");
                }
            }
            struct wifi_mode_info info;
            info.mode = NONE_MODE;
            wifi_get_mode_cur_info(&info);
            if (info.mode == STA_MODE) {
                lwip_static_ip_renew[lwip_netif] = 1;
            }
            if (ntp_get_time_init && !get_time_init && info.mode == STA_MODE) {
                get_time_init = 1;
                thread_fork("ntp_client_get_time", 10, 1024, 0, 0, (void (*)(void *))ntp_client_get_time, NULL);
            }
        }
    }
#ifdef HAVE_EXT_WIRELESS_NETIF
    else if (lwip_netif == EXT_WIFI_NETIF) {
        netdev_get_mac_addr(ext_wireless_netif.hwaddr);
        if (dhcp) {
            dhcp_renew_ipaddr(&ext_wireless_netif);

            tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, &ext_wireless_netif);

            ext_wireless_dhcp_timeout_cnt = 0;

            if (tcpip_timeout(DHCP_TMR_INTERVAL, (sys_timeout_handler)network_is_dhcp_bound, &ext_wireless_netif) != ERR_OK) {
                LWIP_ASSERT("failed to create timeout network_is_dhcp_bound", 0);
            }
        }
    }
#endif
#ifdef HAVE_LTE_NETIF
    else if (lwip_netif == LTE_NETIF) {
        u8 *lte_module_get_mac_addr(void);
        memcpy(lte_netif.hwaddr, lte_module_get_mac_addr(), 6);
        if (dhcp) {
            dhcp_renew_ipaddr(&lte_netif);

            tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, &lte_netif);

            lte_dhcp_timeout_cnt = 0;

            if (tcpip_timeout(DHCP_TMR_INTERVAL, (sys_timeout_handler)network_is_dhcp_bound, &lte_netif) != ERR_OK) {
                LWIP_ASSERT("failed to create timeout network_is_dhcp_bound", 0);
            }
        }
    }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
    else if (lwip_netif == ETH_NETIF) {
        if (dhcp) {
            dhcp_renew_ipaddr(&wire_netif);

            tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, &wire_netif);

            wire_dhcp_timeout_cnt = 0;

            if (tcpip_timeout(DHCP_TMR_INTERVAL, (sys_timeout_handler)network_is_dhcp_bound, &wire_netif) != ERR_OK) {
                LWIP_ASSERT("failed to create timeout network_is_dhcp_bound", 0);
            }
        }
    }
#endif
#ifdef HAVE_BT_NETIF
    else if (lwip_netif == BT_NETIF) {
        if (dhcp) {
            dhcp_renew_ipaddr(&bt_netif);

            tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, &bt_netif);

            bt_dhcp_timeout_cnt = 0;

            if (tcpip_timeout(DHCP_TMR_INTERVAL, (sys_timeout_handler)network_is_dhcp_bound, &bt_netif) != ERR_OK) {
                LWIP_ASSERT("failed to create timeout network_is_dhcp_bound", 0);
            }
        }
    }
#endif
}

void lwip_renew(u8_t lwip_netif, u8_t dhcp)
{
    int err;
    unsigned int parm;
    parm = lwip_netif;
    parm <<= 8;
    parm |= dhcp;
    err = tcpip_callback((tcpip_callback_fn)__lwip_renew, (void *)parm);
    LWIP_ASSERT("failed to lwip_renew tcpip_callback", err == 0);
}

void lwip_dhcp_release_and_stop(u8_t lwip_netif)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

    lwip_static_ip_renew[lwip_netif] = 0;

    tcpip_untimeout((sys_timeout_handler)network_is_dhcp_bound, netif);

    int err = tcpip_callback((tcpip_callback_fn)dhcp_release_and_stop, (void *)netif);
    LWIP_ASSERT("failed to dhcp_release_and_stop tcpip_callback", err == 0);
}

//添加静态arp映射
void lwip_etharp_add_static_entry(const char *ip_str, const char mac[])
{
    struct eth_addr ethaddr;
    memcpy(ethaddr.addr, mac, 6);

    ip4_addr_t dest_ipaddr;
    ip4addr_aton(ip_str, &dest_ipaddr);

    printf("add static entry succeeded. IP=%s", inet_ntoa(dest_ipaddr));

    etharp_add_static_entry(&dest_ipaddr, &ethaddr);
}

//移除静态arp映射
void lwip_etharp_remove_static_entry(const char *ip_str)
{
    ip4_addr_t ipaddr;
    ip4addr_aton(ip_str, &ipaddr);
    printf("remove static entry succeeded. IP=%s", inet_ntoa(ipaddr));
    etharp_remove_static_entry(&ipaddr);
}

/**
* @brief Init_LwIP initialize the LwIP
*/
/*
 * 函数名：LWIP_Init
 * 描述  ：初始化LWIP协议栈，主要是把网卡与LWIP连接起来。
 			包括IP、MAC地址，接口函数
 * 输入  ：是否使用DHCP获得IP地址
 * 输出  : 无
 * 调用  ：外部调用
 */
__attribute__((always_inline_when_const_args))
void Init_LwIP(u8_t lwip_netif)
{
    err_t err = -1;
    sys_sem_t sem;
    struct ip4_addr ipaddr;
    struct ip4_addr netmask;
    struct ip4_addr gw;

    char host_name[32] = {0};
    struct netif *netif = NULL;
    netif_init_fn ethernetif_init = NULL;

    struct lan_setting *lan_setting_info = net_get_lan_info(lwip_netif);
    if (!lan_setting_info) {
        return;
    }

    switch (lwip_netif) {
#ifdef HAVE_ETH_WIRE_NETIF
    case ETH_NETIF:
        netif = &wire_netif;
        ethernetif_init = wired_ethernetif_init;
        sprintf(host_name, "%s", LOCAL_WIRE_HOST_NAME);
        break;
#endif

    case WIFI_NETIF:
        netif = &wireless_netif;
        ethernetif_init = wireless_ethernetif_init;
        sprintf(host_name, "%s", LOCAL_WIRELESS_HOST_NAME);
        break;

#ifdef HAVE_WRIELESS_RAW_NETIF
    case WIFI_RAW_NETIF:
        netif = &wireless_raw_netif;
        ethernetif_init = wireless_raw_ethernetif_init;
        sprintf(host_name, "%s", LOCAL_WIRELESS_HOST_NAME);
        break;
#endif

#ifdef HAVE_EXT_WIRELESS_NETIF
    case EXT_WIFI_NETIF:
        netif = &ext_wireless_netif;
        ethernetif_init = ext_wireless_ethernetif_init;
        sprintf(host_name, "%s", LOCAL_EXT_WIRELESS_HOST_NAME);
        break;
#endif

#ifdef HAVE_BT_NETIF
    case BT_NETIF:
        netif = &bt_netif;
        ethernetif_init = bt_ethernetif_init;
        sprintf(host_name, "%s", LOCAL_BT_HOST_NAME);
        break;
#endif

#ifdef HAVE_LTE_NETIF
    case LTE_NETIF:
        netif = &lte_netif;
        ethernetif_init = lte_ethernetif_init;
        sprintf(host_name, "%s", LOCAL_LTE_HOST_NAME);
        break;
#endif

    default:
        printf("no support netif = %d\n", lwip_netif);
        return;
    }

    if (netif->input) {
        return;
    }

    printf("|Init_LwIP [%d]\n", lwip_netif);

    static u8 lwip_inited;
    if (!lwip_inited) {
        if (sys_sem_new(&sem, 0) != ERR_OK) {
            LWIP_ASSERT("failed to create sem", 0);
        }

        tcpip_init(TcpipInitDone, &sem);
        sys_sem_wait(&sem);
        sys_sem_free(&sem);
        LWIP_DEBUGF(TCPIP_DEBUG, ("tcpip_init: initialized\n"));
        lwip_inited = 1;
    }

    IP4_ADDR(&ipaddr, lan_setting_info->WIRELESS_IP_ADDR0, lan_setting_info->WIRELESS_IP_ADDR1, lan_setting_info->WIRELESS_IP_ADDR2, lan_setting_info->WIRELESS_IP_ADDR3);
    IP4_ADDR(&netmask, lan_setting_info->WIRELESS_NETMASK0, lan_setting_info->WIRELESS_NETMASK1, lan_setting_info->WIRELESS_NETMASK2, lan_setting_info->WIRELESS_NETMASK3);
    IP4_ADDR(&gw, lan_setting_info->WIRELESS_GATEWAY0, lan_setting_info->WIRELESS_GATEWAY1, lan_setting_info->WIRELESS_GATEWAY2, lan_setting_info->WIRELESS_GATEWAY3);

    /*初始化网卡与LWIP的接口，参数为网络接口结构体、ip地址、
    子网掩码、网关、网卡信息指针、初始化函数、输入函数*/
    netif_add(netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init, (netif_input_fn)&tcpip_input);

#if DNS_LOCAL_HOSTLIST
    err = dns_local_addhost(host_name, &netif->ip_addr);
    if (err != ERR_OK) {
        printf("dns_local_addhost err = %d\n", err);
    }
#endif
    /*  When the dev_netif is fully configured this function must be called.*/

#ifndef LWIP_HOOK_IP4_ROUTE_SRC
    /*设置默认网卡 .*/
    netif_set_default(netif);
#endif

    /*设置多播网卡*/
    //ip4_set_default_multicast_netif(&wire_netif);
    /*-------------------------------------------------------------------------------------------------*/

    Display_IPAddress();
}

/*The gethostname function retrieves the standard host name for the local computer.*/
int gethostname(char *name, int namelen)
{
    if (wireless_netif.flags) {
        strncpy(name, LOCAL_WIRELESS_HOST_NAME, namelen);
    }
#ifdef HAVE_EXT_WIRELESS_NETIF
    else if (ext_wireless_netif.flags) {
        strncpy(name, LOCAL_EXT_WIRELESS_HOST_NAME, namelen);
    }
#endif
#ifdef HAVE_LTE_NETIF
    else if (lte_netif.flags) {
        strncpy(name, LOCAL_LTE_HOST_NAME, namelen);
    }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
    else if (wire_netif.flags) {
        strncpy(name, LOCAL_WIRE_HOST_NAME, namelen);
    }
#endif
#ifdef HAVE_BT_NETIF
    else if (bt_netif.flags) {
        strncpy(name, LOCAL_BT_HOST_NAME, namelen);
    }
#endif

    name[namelen - 1] = 0;

    return 0;
}

int getdomainname(char *name, int namelen)
{
    if (wireless_netif.flags) {
        strncpy(name, "www."LOCAL_WIRELESS_HOST_NAME".com", namelen);
    }
#ifdef HAVE_EXT_WIRELESS_NETIF
    else if (ext_wireless_netif.flags) {
        strncpy(name, "www."LOCAL_EXT_WIRELESS_HOST_NAME".com", namelen);
    }
#endif
#ifdef HAVE_LTE_NETIF
    else if (lte_netif.flags) {
        strncpy(name, "www."LOCAL_LTE_HOST_NAME".com", namelen);
    }
#endif
#ifdef HAVE_ETH_WIRE_NETIF
    else if (wire_netif.flags) {
        strncpy(name, "www."LOCAL_WIRE_HOST_NAME".com", namelen);
    }
#endif
#ifdef HAVE_BT_NETIF
    else if (bt_netif.flags) {
        strncpy(name, "www."LOCAL_BT_HOST_NAME".com", namelen);
    }
#endif

    name[namelen - 1] = 0;

    return 0;
}

u32_t sys_now(void)
{
    return OSGetTime() * 10;
}

/**
  * @brief  Called when a frame is received
  * @param  None
  * @retval None
  */
void LwIP_Pkt_Handle(void)
{
}

int getnameinfo(const struct sockaddr *sa, int salen, char *host, int hostlen, char *serv, int servlen, int flags)
{
    struct sockaddr_in *sa_in = (struct sockaddr_in *)sa;

    if ((flags & NI_NUMERICHOST) && host) {
        if (sa_in->sin_addr.s_addr == 0) {
            Get_IPAddress(WIFI_NETIF, host);	//如果没有指定源IP地址就默认使用本地的无线网卡IP
        } else {
            inet_ntoa_r(sa_in->sin_addr.s_addr, host, hostlen);
        }
    }

    if ((flags & NI_NUMERICSERV) && serv) {
        itoa(htons(sa_in->sin_port), serv, 10);
        /* sprintf(serv, "%s", htons(sa_in->sin_port)); */
        serv[servlen - 1] = '\0';
    }

    return 0;
}

char *strerror(int errnum)
{
    return "not_define_strerror";
}

#if 0//def LWIP_HOOK_IP4_ROUTE_SRC
struct netif *
ip4_route2(const ip4_addr_t *src, const ip4_addr_t *dest)
{

//    printf("222  src 0x%x  dest 0x%x \n\n",src,dest);
    if (src == NULL) {
        printf("src is NULL\n\n");
        return NULL;
    }

    if (dest == NULL) {
        printf("dest is NULl \n\n");
        return NULL;
    }

    struct netif *netif;

#if 0//LWIP_MULTICAST_TX_OPTIONS

    /* Use administratively selected interface for multicast by default */
    if (ip4_addr_ismulticast(dest) && ip4_default_multicast_netif) {
        return ip4_default_multicast_netif;
    }

#endif /* LWIP_MULTICAST_TX_OPTIONS */

    /* iterate through netifs */


    for (netif = netif_list; netif != NULL; netif = netif->next) {
//      printf("%s   ::::: %d \n\n", __func__, __LINE__);

        /* is the netif up, does it have a link and a valid address? */
        if (netif_is_up(netif) && netif_is_link_up(netif) && !ip4_addr_isany_val(*netif_ip4_addr(netif))) {
            //          printf("%s   ::::: %d \n\n", __func__, __LINE__);
            /* network mask matches? */
            /* printf("src %s \n\n", ip4addr_ntoa(src));                     */
            /* printf("dest %s \n\n", ip4addr_ntoa(dest));                           */
            /* printf("netif %s \n\n", ip4addr_ntoa(netif_ip4_addr(netif)));         */


            //这里拿源来匹配
            //在之前的函数中，目标地址如果不在同一网关中时，往下走，会使用默认网卡。
            if (ip_addr_isany_val(*src) || ip_addr_isbroadcast(src, netif)) {
                if (ip4_addr_netcmp(dest, netif_ip4_addr(netif), netif_ip4_netmask(netif))) {
                    /*         printf("src %s \n\n", inet_ntoa(*src));                     */
                    /* printf("dest %s \n\n", inet_ntoa(*dest));                           */
                    /* printf("netif %s \n\n", inet_ntoa(*netif_ip4_addr(netif)));         */

                    //                printf("%s   ::::: %d \n\n", __func__, __LINE__);
                    /* return netif on which to forward IP packet                        */
                    return netif;
                }

            } else {
                if (ip4_addr_netcmp(src, netif_ip4_addr(netif), netif_ip4_netmask(netif))) {
                    /* if (ip4_addr_cmp(src, netif_ip4_addr(netif))) { */
                    //              printf("%s   ::::: %d \n\n", __func__, __LINE__);
                    /* return netif on which to forward IP packet */
                    return netif;

                }

            }

            /* gateway matches on a non broadcast interface? (i.e. peer in a point to point interface) */
            if (((netif->flags & NETIF_FLAG_BROADCAST) == 0) && ip4_addr_cmp(dest, netif_ip4_gw(netif))) {
                /* return netif on which to forward IP packet */
                return netif;
            }
        }
    }

#if LWIP_NETIF_LOOPBACK && !LWIP_HAVE_LOOPIF

    /* loopif is disabled, looopback traffic is passed through any netif */
    if (ip4_addr_isloopback(dest)) {
        /* don't check for link on loopback traffic */
        if (netif_is_up(netif_default)) {
            return netif_default;
        }

        /* default netif is not up, just use any netif for loopback traffic */
        for (netif = netif_list; netif != NULL; netif = netif->next) {
            if (netif_is_up(netif)) {
                return netif;
            }
        }

        return NULL;
    }

#endif /* LWIP_NETIF_LOOPBACK && !LWIP_HAVE_LOOPIF */

//造成递归
    /* #if 0                                            */
    /* #ifdef LWIP_HOOK_IP4_ROUTE_SRC                   */

    /*     netif = LWIP_HOOK_IP4_ROUTE_SRC(dest, NULL); */

    /*     if(netif != NULL) {                          */
    /*         return netif;                            */
    /*     }                                            */

    /* #elif defined(LWIP_HOOK_IP4_ROUTE)               */
    /*     netif = LWIP_HOOK_IP4_ROUTE(dest);           */

    /*     if(netif != NULL) {                          */
    /*         return netif;                            */
    /*     }                                            */

    /* #endif                                           */
    /* #endif                                           */

    if ((netif_default == NULL) || !netif_is_up(netif_default) || !netif_is_link_up(netif_default) ||
        ip4_addr_isany_val(*netif_ip4_addr(netif_default))) {
        /* No matching netif found and default netif is not usable.
           If this is not good enough for you, use LWIP_HOOK_IP4_ROUTE() */
        LWIP_DEBUGF(IP_DEBUG | LWIP_DBG_LEVEL_SERIOUS, ("ip4_route: No route to %"U16_F".%"U16_F".%"U16_F".%"U16_F"\n",
                    ip4_addr1_16(dest), ip4_addr2_16(dest), ip4_addr3_16(dest), ip4_addr4_16(dest)));
        IP_STATS_INC(ip.rterr);
        MIB2_STATS_INC(mib2.ipoutnoroutes);
        return NULL;
    }

    return netif_default;
}
#endif

int lwip_get_dest_hwaddr(u8_t lwip_netif, ip4_addr_t *ipaddr, struct eth_addr *dhwaddr)
{
    int ret = -1;
    struct eth_addr *eth_ret;
    ip4_addr_t *ipaddr_ret;

    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return ret;
    }

    ret = etharp_find_addr(netif, ipaddr, &eth_ret, (const ip4_addr_t **)(&ipaddr_ret));

    if (ret != -1) {
        memcpy(dhwaddr, eth_ret, sizeof(struct eth_addr));
    } else {
        puts("lwip_get_dest_hwaddr fail!\r\n");
    }

    return (ret == -1) ? -1 : 0;
}

//Change the IP address of a network interface
void lwip_set_netif_ipaddr(const u8_t lwip_netif, const ip4_addr_t *ipaddr)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    netif_set_ipaddr(netif, ipaddr);
}

void lwip_get_netif_info(u8_t lwip_netif, struct netif_info *info)
{
    struct netif *netif = net_get_netif_handle(lwip_netif);
    if (netif == NULL) {
        return;
    }

#if LWIP_IPV4 && LWIP_IPV6
    info->ip = (u32_t)netif->ip_addr.u_addr.ip4.addr;
    info->gw = (u32_t)netif->gw.u_addr.ip4.addr;
    info->netmask = (u32_t)netif->netmask.u_addr.ip4.addr;
#elif LWIP_IPV4
    info->ip = (u32_t)netif->ip_addr.addr;
    info->gw = (u32_t)netif->gw.addr;
    info->netmask = (u32_t)netif->netmask.addr;
#elif LWIP_IPV6

#endif
}

int lwip_dhcp_bound(void)
{
    struct netif *netif = netif_find("wl0");
    if (netif == NULL) { //lwip 未初始化
        return 0;
    }

    if (lwip_static_ip_renew[WIFI_NETIF]) { //静态IP情况下,可以直接通信
        return 1;
    }

    struct dhcp *dhcp = (struct dhcp *)netif_get_client_data(netif, LWIP_NETIF_CLIENT_DATA_INDEX_DHCP);
    if (dhcp == NULL) { //dhcp 未初始化
        return 0;
    }

    if (dhcp->state == DHCP_STATE_BOUND) {
        return 1;
    }

    return 0;
}

