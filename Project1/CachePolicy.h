#pragma once

namespace Cache
{

    template <typename Key, typename Value>
    class CachePolicy
    {
    public:
        virtual ~CachePolicy() {};

        // ��ӻ���ӿ�
        virtual void put(Key key, Value value) = 0;

        // key�Ǵ������  ���ʵ���ֵ�Դ�����������ʽ���� | ���ʳɹ�����true
        virtual bool get(Key key, Value& value) = 0;
        // ������������ҵ�key����ֱ�ӷ���value
        virtual Value get(Key key) = 0;

    };

} // namespace Cache