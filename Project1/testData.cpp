#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "FIFOCache.h"
#include "LRUCache.h"
#include "LFUCache.h"

using namespace Cache;
const int CACHE_COUNT = 3; //缓存策略数量


//统计并打印每种缓存策略在热点数据访问下的命中率
void printResults(const std::vector<int>& hits, const std::vector<int>& gets) {
    std::vector<std::string> names = { "FIFO" ,"LRU","LFU"}; 

    for (int i = 0; i < hits.size(); ++i) {
        double hitRate = gets[i] == 0 ? 0.0 : static_cast<double>(hits[i]) / gets[i];
        std::cout << names[i] << " 命中率: " << (hitRate * 100.0) << "% (" << hits[i] << "/" << gets[i] << ")\n";
    }
}


//少量数据项被频繁访问，而大部分数据访问较少
void testHotDataAccess() {
    std::cout << "\n=== 测试场景1：热点数据访问测试 ===" << std::endl;
	int CAPACITY = 5;
	int OPERATION_COUNT = 1000;
    int HOTKEYS = 2;//hotkey = [0,1]
	int COLDKEYS = 100;//coldkey = [2,3,...,101]

    //智能指针指向基类
    std::vector<std::shared_ptr<CachePolicy<int, std::string>>> caches = {
        std::make_shared<FIFOCache<int,std::string>>(CAPACITY),
		std::make_shared<LRUCache<int,std::string>>(CAPACITY),
        std::make_shared<LFUCache<int,std::string>>(CAPACITY)
    };

    std::vector<int> hits(CACHE_COUNT);
	std::vector<int> gets(CACHE_COUNT);

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < OPERATION_COUNT; i++) {
        int key;
        bool isPut = (gen() % 100) < 30;
        
        if (gen() % 100 < 70) {//决定访问的数据
			key = gen() % HOTKEYS; 
        }
        else {
			key = HOTKEYS + (gen() % COLDKEYS); 
        }

        for (int j = 0; j < CACHE_COUNT; j++) {
            if (isPut) {//写数据
				std::string value = "value_" + std::to_string(key);
				caches[j]->put(key, value);
            }
            else//读数据
            {
				std::string value;
                gets[j]++;
                if (caches[j]->get(key, value)) {
                    hits[j]++;
                }
            }
        }
    }
    printResults(hits, gets);
}

void testLoopPattern() {
}
void testWorkloadShift() {
}

int main() {
    testHotDataAccess();
    testLoopPattern();
    testWorkloadShift();
    return 0;
}