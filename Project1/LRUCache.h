#pragma once
#include "CachePolicy.h"
#include <unordered_map>
#include <map>
#include <list>
#include <deque>

class LRUCache : public CachePolicy {
public:
    LRUCache(int capacity, int k);  // 支持 LRU 和 LRU-k
    bool access(int key) override;

private:
    int capacity;
    int k;
    int timestamp = 0;

    // LRU-1 用的数据结构
    std::list<int> usage;//记录缓存数据的顺序
    std::unordered_map<int, std::list<int>::iterator> usage_map;//记录数据的位置，方便get和put操作

    // LRU-k 用的数据结构
    struct AccessHistory {
        std::deque<int> timestamps;
    };
    std::unordered_map<int, AccessHistory> history;
    std::map<int, int> eviction_order;  // 第k次时间戳 -> key
};
