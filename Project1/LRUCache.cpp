#include "LRUCache.h"

LRUCache::LRUCache(int capacity, int k) : capacity(capacity), k(k) {}

bool LRUCache::access(int key) {
    ++timestamp;

    // ==== LRU-1 特例 ====
    if (k == 1) {
        if (usage_map.count(key)) {
            usage.erase(usage_map[key]);
            usage.push_front(key);
            usage_map[key] = usage.begin();
            return true;
        }

        if ((int)usage.size() >= capacity) {
            int old = usage.back();
            usage.pop_back();
            usage_map.erase(old);
        }

        usage.push_front(key);
        usage_map[key] = usage.begin();
        return false;
    }

    // ==== LRU-k 通用情况 ====
    auto& h = history[key];
    if ((int)h.timestamps.size() == k) {
        eviction_order.erase(h.timestamps.front());
    }

    h.timestamps.push_back(timestamp);
    if ((int)h.timestamps.size() > k)
        h.timestamps.pop_front();

    if ((int)h.timestamps.size() == k) {
        eviction_order[h.timestamps.front()] = key;
    }

    if ((int)history.size() > capacity) {
        int victim = eviction_order.begin()->second;
        eviction_order.erase(eviction_order.begin());
        history.erase(victim);
    }

    return h.timestamps.size() >= k;
}
