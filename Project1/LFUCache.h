// include/LFUCache.h
#pragma once
#include "CachePolicy.h"
#include <unordered_map>
#include <map>

class LFUCache : public CachePolicy {
public:
    explicit LFUCache(int capacity);
    bool access(int key) override;

private:
    int capacity, timestamp = 0;
    struct Entry { int freq, time; };
    std::unordered_map<int, Entry> data;
    std::map<std::pair<int, int>, int> freqOrder;
};
