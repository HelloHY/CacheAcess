// include/FIFOCache.h
#pragma once
#include "CachePolicy.h"
#include <queue>
#include <unordered_set>

class FIFOCache : public CachePolicy {
public:
    explicit FIFOCache(int capacity);
    bool access(int key) override;

private:
    int capacity;
    std::queue<int> order;
	std::unordered_set<int> cache;//����O(1)�������vector�����O(n)
};
