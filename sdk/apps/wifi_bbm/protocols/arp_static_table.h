
#ifndef _ARP_STATIC_TABLE_H
#define _ARP_STATIC_TABLE_H

#include "lwip.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "os/os_api.h"
#include "syscfg/syscfg_id.h"

//最大支持多少个静态ARP映射
#define MAX_ARP_STATIC_ENTRY (6)

enum arp_state_t {
    ARP_STATE_EMPTY = 0,
    ARP_STATE_USED,
};

struct arp_entry_t {
    ip4_addr_t ipaddr;
    struct eth_addr ethaddr;
    u8_t state;
};

struct arp_static_table {
    unsigned char id;
    unsigned char ip_cnt;
    struct arp_entry_t arp_table[MAX_ARP_STATIC_ENTRY];
};

void arp_static_table_init(void);
struct arp_entry_t *arp_static_entry_alloc(unsigned char i);
const struct arp_entry_t *get_arp_static_entry_by_id(const unsigned char id);

#endif
