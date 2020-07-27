#pragma once
#include "List.h"
class Queue 
{
private:
    List<int> m_Items;
public:
    ~Queue();
    void MakeEmpty();
    bool IsEmpty();
    void Enqueue(int i_Value);
    int Dequeue();
};