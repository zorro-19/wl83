
#include "pairing_data_model.h"
#include "system/includes.h"

//配对方式
//Pairing request
//Paired response
//Paired ACK

#define PAIRING_REQUEST "{\"type\":\"pair_req\", \"uuid\":\"%s\", \"data\" :{\"ip\":\"192.168.1.1\", \"mac\":\"888888888888\"}}"
#define PAIRING_RESPONE "{\"type\": \"pair_rsp\", \"uuid\": \"%s\"}"

//组包格式：magic(4 bytes)|数据长度(4 bytes) | data
//通过type类型来区分不同的报文消息
int package_assembly(char *data, int data_len, char *package, int package_buf_len)
{
    if (data == NULL || data_len <= 0 || package == NULL || (data_len + 8) > package_buf_len) {
        return -1;
    }

    package_head head;
    head.magic = PACKAGE_MAGIC;
    head.len = data_len;

    memcpy(package, &head, sizeof(package_head));
    memcpy(package + sizeof(package_head), data, data_len);

    return (data_len + sizeof(package_head));
}

//example
int pairing_request_assembly(char *buf, int buf_len)
{
    unsigned char tmp[128];
    snprintf(tmp, sizeof(tmp), PAIRING_REQUEST,
             "1234567890");

    return package_assembly(tmp, strlen(tmp), buf, buf_len);
}

int get_package_payload_len(const char *buf)
{
    package_head *head = (package_head *)buf;
    if (head->magic !=  PACKAGE_MAGIC) {
        return -1;
    }

    return head->len;
}



