#pragma once

#include "CachePolicy.h"
#include <cstddef>
#include <unordered_map>
#include <list>

namespace Cache {

	template <typename Key, typename Value>
	class LFUCache : public CachePolicy<Key, Value> {
	public:
		LFUCache(size_t capacity);
		void put(Key key, Value value) override;
		bool get(Key key, Value& value) override;
		Value get(Key key) override;

	private:
		size_t _capacity;
		std::unordered_map<Key, Value> _keyToVal;
		std::unordered_map<Key, int> _keyToFreq;
		std::unordered_map<int, std::list<Key>> _freqToList;
		std::unordered_map<Key, typename std::list<Key>::iterator> _keyToIter;
		int _minFreq = 0;

		void updateFreq(Key key);
	};
}
