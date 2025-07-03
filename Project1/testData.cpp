#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "FIFOCache.h"
#include "LRUCache.h"
#include "LFUCache.h"

void testHotDataAccess(CachePolicy& policy, const std::string& name) {
    const int CAPACITY = 30;
    const int HOTKEY = 40;   // �ȵ����� [0, HOTKEY)
    const int COLDKEY = 70;  // �����ݴ� HOTKEY �� HOTKEY+COLDKEY
    const int OPERATIONS = 1000;

    srand(time(0));
    int hit = 0;

    // ģ�����
    for (int i = 0; i < OPERATIONS; ++i) {
        bool isPut = rand() % 5 == 0; // 20% put ����

        int key;
        if (rand() % 100 < 70) { // 70% ������
            key = rand() % HOTKEY;
        }
        else {
            key = HOTKEY + rand() % COLDKEY;
        }

        // ʵ������ treat put/get һ������Ϊ cache.access ����벢����
        if (policy.access(key)) {
            hit++;
        }
    }

    std::cout << name << " HIT RATE = " << (double)hit / OPERATIONS * 100 << "%" << std::endl;
}

int main() {
    const int CAPACITY = 30;

    std::unique_ptr<CachePolicy> fifo = std::make_unique<FIFOCache>(CAPACITY);
    std::unique_ptr<CachePolicy> lru = std::make_unique<LRUCache>(CAPACITY);
    std::unique_ptr<CachePolicy> lfu = std::make_unique<LFUCache>(CAPACITY);

    testHotDataAccess(*fifo, "FIFO");
    testHotDataAccess(*lru, "LRU");
    testHotDataAccess(*lfu, "LFU");

    return 0;
}