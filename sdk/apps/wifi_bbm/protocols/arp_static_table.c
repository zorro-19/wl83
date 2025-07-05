#include "app_config.h"
#include "arp_static_table.h"

static OS_MUTEX g_mutex;
#define ARP_MUTEX_INITIALIZE()       os_mutex_create(&g_mutex)
#define ARP_MUTEX_LOCK()             os_mutex_pend(&g_mutex, 0)
#define ARP_MUTEX_UNLOCK()           os_mutex_post(&g_mutex)

static struct arp_static_table g_arp_table = {0};
static u8 g_mac[6];

//初始化静态的arp映射表
void arp_static_table_init(void)
{
    int i;
    u8 src_mac[6];
    ARP_MUTEX_INITIALIZE();
    struct arp_static_table *ptr = &g_arp_table;
    int ret = syscfg_read(BBM_RX_ARP_INDEX, ptr, sizeof(g_arp_table));
    if (ret < 0) {
        memset(&g_arp_table, 0x00, sizeof(g_arp_table));
    }

    wifi_raw_get_mac(src_mac);
    for (i = 0; i < ARRAY_SIZE(src_mac); i++) {
        src_mac[i] += 1;
    }
    memcpy(g_mac, src_mac, sizeof(g_mac));

    for (i = 0; i < MAX_ARP_STATIC_ENTRY; i++) {
        if (ptr->arp_table[i].state == ARP_STATE_USED) {
            printf("add static entry id:%d \n", i);
            lwip_etharp_add_static_entry(inet_ntoa(ptr->arp_table[i].ipaddr), ptr->arp_table[i].ethaddr.addr);
        }
    }
}

void arp_static_table_update_to_flash(void)
{
    ARP_MUTEX_LOCK();
    char *ptr = (char *)&g_arp_table;
    int ret = syscfg_write(BBM_RX_ARP_INDEX, ptr, sizeof(g_arp_table));
    if (ret < 0) {
        printf("arp_static_table_update_to_flash err!!!\n");
    }
    ARP_MUTEX_UNLOCK();
}

void arp_static_table_reset_to_flash(void)
{
    int ip_cnt = g_arp_table.ip_cnt;
    memset(&g_arp_table, 0x00, sizeof(g_arp_table));
    g_arp_table.ip_cnt = ip_cnt;
    char *ptr = (char *)&g_arp_table;
    int ret = syscfg_write(BBM_RX_ARP_INDEX, ptr, sizeof(g_arp_table));
    if (ret < 0) {
        printf("arp_static_table_update_to_flash err!!!\n");
    }
}

struct arp_entry_t *arp_static_entry_alloc(unsigned char i)
{
    struct ip4_addr ip_address;
    struct arp_static_table *table_prt = &g_arp_table;
    unsigned char ip_cnt = table_prt->ip_cnt ;
    struct lan_setting *lan_setting_info = net_get_lan_info(WIFI_RAW_NETIF);
    char entry_id;

    ARP_MUTEX_LOCK();
    if (table_prt->ip_cnt + lan_setting_info->CLIENT_IPADDR4 == 255) {
        table_prt->ip_cnt = 0;
    }

    table_prt->ip_cnt++;

    IP4_ADDR(&ip_address, lan_setting_info->CLIENT_IPADDR1, \
             lan_setting_info->CLIENT_IPADDR2, lan_setting_info->CLIENT_IPADDR3, table_prt->ip_cnt + lan_setting_info->CLIENT_IPADDR4);

    /* unsigned char i; */
    /* for (i = 0; i < MAX_ARP_STATIC_ENTRY; i++) { */
    if (table_prt->arp_table[i].state == ARP_STATE_EMPTY) {
        memcpy(table_prt->arp_table[i].ethaddr.addr, g_mac, 6);
        table_prt->arp_table[i].ipaddr = *(ip4_addr_t *)&ip_address;
        table_prt->arp_table[i].state = ARP_STATE_USED;
        lwip_etharp_add_static_entry(inet_ntoa(table_prt->arp_table[i].ipaddr), table_prt->arp_table[i].ethaddr.addr);
        printf("arp_static_entry_alloc: ip[%s], mac[%x:%x:%x:%x:%x:%x]", inet_ntoa(table_prt->arp_table[i].ipaddr), \
               table_prt->arp_table[i].ethaddr.addr[0],
               table_prt->arp_table[i].ethaddr.addr[1],
               table_prt->arp_table[i].ethaddr.addr[2],
               table_prt->arp_table[i].ethaddr.addr[3],
               table_prt->arp_table[i].ethaddr.addr[4],
               table_prt->arp_table[i].ethaddr.addr[5]
              );
        ARP_MUTEX_UNLOCK();
        return &table_prt->arp_table[i];
    }
    /* } */

    ARP_MUTEX_UNLOCK();
    return NULL;
}

void arp_static_entry_free(unsigned char id)
{
    ARP_MUTEX_LOCK();
    struct arp_static_table *table_prt = &g_arp_table;
    table_prt->arp_table[id].state = ARP_STATE_EMPTY;
    printf("lwip_etharp_remove_static_entry: %s\n", inet_ntoa(table_prt->arp_table[id].ipaddr));
    //lwip中加入arp静态映射
    lwip_etharp_remove_static_entry(inet_ntoa(table_prt->arp_table[id].ipaddr));
    ARP_MUTEX_UNLOCK();
}

const struct arp_entry_t *get_arp_static_entry_by_id(const unsigned char id)
{
    ARP_MUTEX_LOCK();
    struct arp_static_table *table_prt = &g_arp_table;
    if (id < MAX_ARP_STATIC_ENTRY && table_prt->arp_table[id].state == ARP_STATE_USED) {
        ARP_MUTEX_UNLOCK();
        return &table_prt->arp_table[id];
    }

    ARP_MUTEX_UNLOCK();
    return NULL;
}

const struct arp_entry_t *get_arp_static_entry_by_ip(const char *ip_str)
{
    ARP_MUTEX_LOCK();
    struct arp_static_table *table_prt = &g_arp_table;
    char i;
    for (i = 0; i < MAX_ARP_STATIC_ENTRY; i++) {
        if ((table_prt->arp_table[i].state == ARP_STATE_USED) && (0 == strcmp(ip_str, inet_ntoa(table_prt->arp_table[i].ipaddr)))) {
            ARP_MUTEX_UNLOCK();
            return &table_prt->arp_table[i];
        }
    }

    ARP_MUTEX_UNLOCK();
    return NULL;
}

const struct arp_entry_t *get_arp_static_entry_by_ethaddr(const char mac[6])
{
    ARP_MUTEX_LOCK();
    struct arp_static_table *table_prt = &g_arp_table;
    char i;
    for (i = 0; i < MAX_ARP_STATIC_ENTRY; i++) {
        if ((table_prt->arp_table[i].state == ARP_STATE_USED) && (0 == memcmp(table_prt->arp_table[i].ethaddr.addr, mac, 6))) {
            ARP_MUTEX_UNLOCK();
            return &table_prt->arp_table[i];
        }
    }

    ARP_MUTEX_UNLOCK();
    return NULL;
}

void arp_static_table_test(void)
{
#if 0
    arp_static_table_init();
    char id = arp_static_entry_alloc();
    if (id < 0) {
        printf("arp_static_entry_alloc err!\n");
        return ;
    }
    printf("alloc id: %d\n", id);

    struct arp_entry_t *entry_t = get_arp_static_entry_by_id(id);
    if (entry_t) {
        printf("entry_t: ip[%s], mac[%x:%x:%x:%x:%x:%x]", inet_ntoa(entry_t->ipaddr), \
               entry_t->ethaddr.addr[0],
               entry_t->ethaddr.addr[1],
               entry_t->ethaddr.addr[2],
               entry_t->ethaddr.addr[3],
               entry_t->ethaddr.addr[4],
               entry_t->ethaddr.addr[5]
              );
    }

    arp_static_entry_free(id);
#endif
}

