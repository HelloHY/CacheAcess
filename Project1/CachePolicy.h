// include/CachePolicy.h
#ifndef CACHE_POLICY_H
#define CACHE_POLICY_H

class CachePolicy {
public:
    virtual bool access(int key) = 0; // 返回 true 表示命中
    virtual ~CachePolicy() {}
};

#endif // CACHE_POLICY_H