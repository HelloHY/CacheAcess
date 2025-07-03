// src/FIFOCache.cpp
#include "FIFOCache.h"

FIFOCache::FIFOCache(int capacity) : capacity(capacity) {}

bool FIFOCache::access(int key) {
    if (cache.count(key)) return true;

    if (cache.size() >= capacity) {
        int old = order.front(); 
        order.pop();
        cache.erase(old);
    }

    cache.insert(key);
    order.push(key);
    return false;
}
