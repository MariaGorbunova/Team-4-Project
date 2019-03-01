
#ifndef ENTRY_H
#define ENTRY_H
#include "iPhone.h"
const int bucketsNum = 3;
class entry
{
private:
    iPhone * bucket[bucketsNum];
    int count;

public:
    // Constructor
    entry()
    {
        for(int i=0; i<bucketsNum; i++) bucket[i] = nullptr;
        count = 0;
    }

    /// getters
    iPhone* getBucket(int i)
    {
        return bucket[i];
    }

    int getCount()
    {
        return count;
    }

    /// setters
    void setBucket(int i, iPhone* ptr)
    {
        bucket[i] = ptr;
    }

    void increseCount()
    {
        count++;
    }

    void decreaseCount()
    {
        count--;
    }
};

#endif
