#include <stdexcept>
#include <iostream>
#include "FIFOCache.h"

namespace Cache {

    template <typename Key, typename Value>
    FIFOCache<Key, Value>::FIFOCache(size_t capacity) : _capacity(capacity) {}

    template <typename Key, typename Value>
    void FIFOCache<Key, Value>::put(Key key, Value value) {
        if (_cache.find(key) != _cache.end()) {
            _cache[key] = value; // 更新值
            return;
        }

        if (_cache.size() >= _capacity) {
            Key old_key = _order.front();
            _order.pop();
            _cache.erase(old_key);
        }

        _order.push(key);
        _cache[key] = value;
    }

    template <typename Key, typename Value>
    bool FIFOCache<Key, Value>::get(Key key, Value& value) {
        auto it = _cache.find(key);
        if (it == _cache.end()) return false;
        value = it->second;
        return true;
    }

    template <typename Key, typename Value>
    Value FIFOCache<Key, Value>::get(Key key) {
        auto it = _cache.find(key);
        if (it == _cache.end()) throw std::out_of_range("Key not found in FIFO cache");
        return it->second;
    }

    // 显式模板实例化
    template class FIFOCache<int, std::string>;
    // 可按需添加更多类型
}

