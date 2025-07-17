#pragma once

#include "CachePolicy.h"
#include <cstddef>
#include <unordered_map>
#include <queue>

namespace Cache {

	template <typename Key, typename Value>
	class FIFOCache : public CachePolicy<Key, Value> {
	public:
		FIFOCache(size_t capacity);
		void put(Key key, Value value) override;
		bool get(Key key, Value& value) override;
		Value get(Key key) override;

	private:
		size_t _capacity;
		std::unordered_map<Key, Value> _cache;//快速存储和查找 key → value 映射。
		std::queue<Key> _order;//记录插入顺序

	};
}
