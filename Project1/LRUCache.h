#pragma once

#include "CachePolicy.h"
#include <list>
#include <unordered_map>


namespace Cache {
	template <typename Key, typename Value>
	class LRUCache :public CachePolicy<Key, Value> {
	public:
		LRUCache(size_t capacity);
		void put(Key key, Value value) override;
		bool get(Key key, Value& value) override;
		Value get(Key key) override;

	private:
		size_t _capacity;
		std::list<typename std::pair<Key, Value>> _cacheList;//保存访问顺序，最近使用的在前
		std::unordered_map<Key,typename std::list<std::pair<Key, Value>>::iterator> _cacheMap;
		//(key，iterator), so it->second = iterator
	};
}