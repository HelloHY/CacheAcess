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
    const int HOTKEY = 40;   // 热点数据 [0, HOTKEY)
    const int COLDKEY = 70;  // 冷数据从 HOTKEY 到 HOTKEY+COLDKEY
    const int OPERATIONS = 1000;

    srand(time(0));
    int hit = 0;

    // 模拟操作
    for (int i = 0; i < OPERATIONS; ++i) {
        bool isPut = rand() % 5 == 0; // 20% put 操作

        int key;
        if (rand() % 100 < 70) { // 70% 热数据
            key = rand() % HOTKEY;
        }
        else {
            key = HOTKEY + rand() % COLDKEY;
        }

        // 实际我们 treat put/get 一样，因为 cache.access 会插入并驱逐
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