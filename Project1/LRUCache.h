#pragma once
#include "CachePolicy.h"
#include <unordered_map>
#include <map>
#include <list>
#include <deque>

class LRUCache : public CachePolicy {
public:
    LRUCache(int capacity, int k);  // ֧�� LRU �� LRU-k
    bool access(int key) override;

private:
    int capacity;
    int k;
    int timestamp = 0;

    // LRU-1 �õ����ݽṹ
    std::list<int> usage;//��¼�������ݵ�˳��
    std::unordered_map<int, std::list<int>::iterator> usage_map;//��¼���ݵ�λ�ã�����get��put����

    // LRU-k �õ����ݽṹ
    struct AccessHistory {
        std::deque<int> timestamps;
    };
    std::unordered_map<int, AccessHistory> history;
    std::map<int, int> eviction_order;  // ��k��ʱ��� -> key
};
