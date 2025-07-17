#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "FIFOCache.h"
#include "LRUCache.h"
#include "LFUCache.h"

using namespace Cache;
const int CACHE_COUNT = 3; //�����������


//ͳ�Ʋ���ӡÿ�ֻ���������ȵ����ݷ����µ�������
void printResults(const std::vector<int>& hits, const std::vector<int>& gets) {
    std::vector<std::string> names = { "FIFO" ,"LRU","LFU"}; 

    for (int i = 0; i < hits.size(); ++i) {
        double hitRate = gets[i] == 0 ? 0.0 : static_cast<double>(hits[i]) / gets[i];
        std::cout << names[i] << " ������: " << (hitRate * 100.0) << "% (" << hits[i] << "/" << gets[i] << ")\n";
    }
}


//���������Ƶ�����ʣ����󲿷����ݷ��ʽ���
void testHotDataAccess() {
    std::cout << "\n=== ���Գ���1���ȵ����ݷ��ʲ��� ===" << std::endl;
	int CAPACITY = 5;
	int OPERATION_COUNT = 1000;
    int HOTKEYS = 2;//hotkey = [0,1]
	int COLDKEYS = 100;//coldkey = [2,3,...,101]

    //����ָ��ָ�����
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
        
        if (gen() % 100 < 70) {//�������ʵ�����
			key = gen() % HOTKEYS; 
        }
        else {
			key = HOTKEYS + (gen() % COLDKEYS); 
        }

        for (int j = 0; j < CACHE_COUNT; j++) {
            if (isPut) {//д����
				std::string value = "value_" + std::to_string(key);
				caches[j]->put(key, value);
            }
            else//������
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