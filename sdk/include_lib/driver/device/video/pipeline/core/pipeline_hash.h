#ifndef _PIPELINE_HASH_H
#define _PIPELINE_HASH_H

#define HASH_TABLE_SIZE   1024  // 哈希表最大长度

// 定义键值对的类型
typedef char *H_KEY_TYPE;    // key类型
typedef int  H_VALUE_TYPE; // value类型

typedef struct {
    H_KEY_TYPE key;
    H_VALUE_TYPE value;
} kv_table_t;

// 单个哈希节点定义
typedef struct hashnode_s {
    H_KEY_TYPE key;
    H_VALUE_TYPE value;
    struct hashnode_s *next;
} hashnode_t;

// 哈希表结构体
typedef struct hashtable_s {
    hashnode_t **nodes; // 哈希表头
    int table_size;   // 单个哈希表的最大长度
    int count;      // 哈希表中存储的元素总数
} hashtable_t;
typedef hashtable_t kv_hash_t;

extern kv_hash_t *hash_kv_hdl;


// 初始化
// 参数：kv_h要传地址
// 返回值：0成功，-1失败
int kv_hash_init(kv_hash_t *kv_h);
// 销毁
// 参数：kv_h要传地址
// 返回值：0成功，-1失败
int kv_hash_desy(kv_hash_t *kv_h);
// 插入指令：有就报错，没有就创建
// 返回值：0表示成功、-1表示失败、-2表示已经有key
int kv_hash_set(kv_hash_t *kv_h, kv_table_t table);
// 查找指令
// 返回值：正常返回value，NULL表示没有
int kv_hash_get(kv_hash_t *kv_h, H_KEY_TYPE key);
// 删除指令
// 返回值：0成功，-1失败，-2没有
int kv_hash_delete(kv_hash_t *kv_h, char **tokens);
// 计数指令
int kv_hash_count(kv_hash_t *kv_h);
// 存在指令
// 返回值：1存在，0没有
int kv_hash_exist(kv_hash_t *kv_h, char **tokens);

#endif
