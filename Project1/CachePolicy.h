// include/CachePolicy.h
#ifndef CACHE_POLICY_H
#define CACHE_POLICY_H

class CachePolicy {
public:
    virtual bool access(int key) = 0; // ���� true ��ʾ����
    virtual ~CachePolicy() {}
};

#endif // CACHE_POLICY_H