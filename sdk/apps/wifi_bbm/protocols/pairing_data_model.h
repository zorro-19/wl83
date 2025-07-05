
#ifndef PAIRING_DATA_MODEL_H_
#define PAIRING_DATA_MODEL_H_

//配对
#define PAIRING_REQUEST "{\"type\":\"pair_req\",\"data\" :{\"bbm_rx_ip\":\"%s\",\"bbm_rx_mac\":\"%s\", \"bbm_tx_ip\":\"%s\", \"bbm_tx_mac\":\"%s\",\"wifi_channel\":\"%d\"}}"
#define PAIRING_RESPONE "{\"type\": \"pair_rsp\", \"data\" :{\"bbm_tx_ip\":\"%s\", \"bbm_tx_mac\":\"%s\"}}"
#define PAIRING_ACK "{\"type\":\"pair_ack\"}"
#define PACKAGE_MAX_SIZE    1024


#ifdef __cplusplus
extern "C" {
#endif

//固定magic
#define PACKAGE_MAGIC 0x3f721fb5

typedef struct {
    unsigned int magic;
    unsigned int len;
} package_head;


#ifdef __cplusplus
}
#endif

#endif
