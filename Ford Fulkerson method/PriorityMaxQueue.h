#pragma once
#include "Vertex.h"
#include <iostream>
using namespace std;

class PriorityMaxQueue
{
private:
    Vertex* m_Data;
    int m_MaxHeapSize;
    int m_CurrentHeapSize;
    bool m_Allocated;
    static int Left(int i_Node);
    static int Right(int i_Node);
    static int Parent(int i_Node);
    void FixHeap(int i_Node, int* io_VerticesPlaceInTheHeap);
public:
    PriorityMaxQueue();
    ~PriorityMaxQueue();
    void Build(Vertex* i_Array, int i_ArraySize, int* io_VerticesPlaceInTheHeap);
    Vertex DeleteMax(int* io_VerticesPlaceInTheHeap);
    bool IsEmpty();
    void IncreaseKey(int i_Place, int i_NewKey, int* io_VerticesPlaceInTheHeap);
    void Swap(Vertex* i_FirstEdge, Vertex* i_SecondEdge);
};