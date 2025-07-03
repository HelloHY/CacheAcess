// src/LFUCache.cpp
#include "LFUCache.h"

LFUCache::LFUCache(int capacity) : capacity(capacity) {}

bool LFUCache::access(int key) {
    ++timestamp;

    if (data.count(key)) {
        Entry e = data[key];
        freqOrder.erase({ e.freq, e.time });
        e.freq += 1;
        e.time = timestamp;
        data[key] = e;
        freqOrder[{e.freq, e.time}] = key;
        return true;
    }

    if ((int)data.size() >= capacity) {
        auto victim = freqOrder.begin()->second;
        freqOrder.erase(freqOrder.begin());
        data.erase(victim);
    }

    data[key] = { 1, timestamp };
    freqOrder[{1, timestamp}] = key;
    return false;
}
