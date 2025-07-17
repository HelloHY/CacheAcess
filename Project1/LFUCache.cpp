#include "LFUCache.h"
#include <iostream>

namespace Cache {

	template <typename Key, typename Value>
	LFUCache<Key, Value>::LFUCache(size_t capacity) : _capacity(capacity), _minFreq(0) {}

	template <typename Key, typename Value>
	void LFUCache<Key, Value>::put(Key key, Value value) {
		if (_capacity == 0) return;

		auto it = _keyToVal.find(key);
		if (it != _keyToVal.end()) {//找到key
			_keyToVal[key] = value;
			updateFreq(key);
			return;
		}

		if (_keyToVal.size() >= _capacity) {
			if (_freqToList[_minFreq].empty()) return;
			auto evictKey = _freqToList[_minFreq].back();
			_freqToList[_minFreq].pop_back();
			_keyToVal.erase(evictKey);
			_keyToFreq.erase(evictKey);
			_keyToIter.erase(evictKey);
		}

		_keyToVal[key] = value;
		_keyToFreq[key] = 1;
		_freqToList[1].push_front(key);
		_keyToIter[key] = _freqToList[1].begin();
		_minFreq = 1;
	}

	template <typename Key,typename Value>
	bool LFUCache<Key,Value>::get(Key key, Value& value) {
		auto it = _keyToVal.find(key);
		if (it == _keyToVal.end())//key不存在
			return false;
		value = it->second;
		updateFreq(key);
		return true;
	}

	template <typename Key, typename Value>
	Value LFUCache<Key,Value>::get(Key key) {
		if (!_keyToVal.count(key)) throw std::out_of_range("Key not found");
		updateFreq(key);
		return _keyToVal[key];
	}

	template <typename Key, typename Value>
	void LFUCache<Key,Value>::updateFreq(Key key) {//更新频率:keyToFreq、freqtoList
		int freq = _keyToFreq[key];
		_freqToList[freq].erase(_keyToIter[key]);
		if (_freqToList[freq].empty()) {
			_freqToList.erase(freq);
			if (_minFreq == freq) {
				_minFreq++;
			}
		}

		_keyToFreq[key]++;
		int newFreq = _keyToFreq[key];
		_freqToList[newFreq].push_front(key);
		_keyToIter[key] = _freqToList[newFreq].begin();
	}

	template class LFUCache<int, std::string>;
}