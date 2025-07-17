#include <iostream>
#include <stdexcept>
#include "LRUCache.h"

namespace Cache {
	template <typename Key, typename Value>
	LRUCache<Key, Value>::LRUCache(size_t capacity) : _capacity(capacity) {}
	
	template <typename Key, typename Value>
	void LRUCache<Key, Value>::put(Key key, Value value) {
		//检查是否存在
		auto it = _cacheMap.find(key);
		if (it != _cacheMap.end()) {
		//存在：更新位置
			it->second->second = value;
			_cacheList.splice(_cacheList.begin(), _cacheList, it->second);
		}
		else {
			if (_cacheList.size() >= _capacity && !_cacheList.empty()) {
				//不存在：删掉尾部，插入新元素
				auto last = _cacheList.back();
				_cacheMap.erase(last.first);
				_cacheList.pop_back();
			}
		}
		//插入新元素到头部
		_cacheList.emplace_front(key, value);
		_cacheMap[key] = _cacheList.begin();
	}

	template <typename Key, typename Value>
	bool LRUCache<Key, Value>::get(Key key, Value& value) {
		auto it = _cacheMap.find(key);
		if (it == _cacheMap.end()) {
			return false; // 未找到
		}
		_cacheList.splice(_cacheList.begin(), _cacheList, it->second);
		value = it->second->second;
		return true; // 找到并更新位置
	}

	template <typename Key, typename Value>
	Value LRUCache<Key, Value>::get(Key key) {
		auto it = _cacheMap.find(key);
		if (it == _cacheMap.end()) throw std::out_of_range("Key not found in LRU cache");

		_cacheList.splice(_cacheList.begin(), _cacheList, it->second);
		return it->second->second;
	}
	
	template class LRUCache<int, std::string>;
}