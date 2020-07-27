#include"PriorityMaxQueue.h"
#include "Vertex.h"


PriorityMaxQueue::PriorityMaxQueue()
{
	m_Data = nullptr;
	m_Allocated = false;
	m_CurrentHeapSize = 0;
	m_MaxHeapSize = 0;
}

PriorityMaxQueue::~PriorityMaxQueue()
{
	if (m_Allocated)
	{
		delete[] m_Data;
	}
	m_Data = nullptr;
}

int PriorityMaxQueue::Parent(int i_Node) //return the index of the parent of node
{
	return (i_Node - 1) / 2;
}

int PriorityMaxQueue::Left(int i_Node) // return the index of the left son  
{
	return (2 * i_Node + 1);
}

int PriorityMaxQueue::Right(int i_Node)// return the index of the right son  
{
	return (2 * i_Node + 2);
}

void PriorityMaxQueue::FixHeap(int node,int* io_VerticesPlaceInTheHeap)
{
	int max = node;
	int left = Left(node);
	int right = Right(node);

	// if the key of the head of heap is INF there is no need to fix the heap
	if (m_Data[node].GetCurrentFlow() != INF)
	{
		if ((left < m_CurrentHeapSize) && (m_Data[left].GetCurrentFlow() > m_Data[max].GetCurrentFlow() && m_Data[max].GetCurrentFlow()  != INF || m_Data[left].GetCurrentFlow() == INF))
		{
			// set left son as max if left sons key > his parent key and the parent key != INF or the left son key is INF
			max = left;
		}

		if ((right < m_CurrentHeapSize) && (m_Data[right].GetCurrentFlow() > m_Data[max].GetCurrentFlow() && m_Data[max].GetCurrentFlow() != INF || m_Data[right].GetCurrentFlow() == INF))
		{
			// set right son as max if left sons key > his parent key and the parent key != INF or the left son key is INF
			max = right;
		}

		if (max != node)
		{
			// update places in the auxiliary array
			io_VerticesPlaceInTheHeap[m_Data[node].GetIndex()] = max;
			io_VerticesPlaceInTheHeap[m_Data[max].GetIndex()] = node;
			// swap the elements and continue fixing the heap if needed
			Swap(&m_Data[node], &m_Data[max]);
			FixHeap(max, io_VerticesPlaceInTheHeap);
		}
	}
}

Vertex PriorityMaxQueue::DeleteMax(int* io_VerticesPlaceInTheHeap)
{
	if (m_CurrentHeapSize < 1)
	{
		cout << "Error: EMPTY HEAP\n";
		exit(1);
	}
	// get the head of the heap and update heap size
	Vertex max = m_Data[0];
	m_CurrentHeapSize--;
	// update places in the auxiliary array
	io_VerticesPlaceInTheHeap[m_Data[0].GetIndex()] = -1; // mark element that is out of the heap
	io_VerticesPlaceInTheHeap[m_Data[m_CurrentHeapSize].GetIndex()] = 0; 
	m_Data[0] = m_Data[m_CurrentHeapSize];
	// fix the updated heap
	FixHeap(0, io_VerticesPlaceInTheHeap);
	return max;
}

bool PriorityMaxQueue::IsEmpty() // check if the heap is empty
{
	return m_CurrentHeapSize == 0;
}

void PriorityMaxQueue:: Swap(Vertex* i_FirstEdge, Vertex* i_SecondEdge) // swap elements in the heap
{
	Vertex tempVertex = *i_FirstEdge;
	*i_FirstEdge = *i_SecondEdge;
	*i_SecondEdge = tempVertex;
}

void PriorityMaxQueue::Build(Vertex* i_Array, int i_ArraySize, int* io_VerticesPlaceInTheHeap) // build heap from array using floyd algorithm
{
	m_CurrentHeapSize = m_MaxHeapSize = i_ArraySize;

	m_Data = i_Array;
	m_Allocated = false;

	for (int i = m_CurrentHeapSize / 2 - 1; i >= 0; i--)
	{
		FixHeap(i, io_VerticesPlaceInTheHeap);
	}
}

void PriorityMaxQueue::IncreaseKey(int i_Place, int i_NewKey, int* io_VerticesPlaceInTheHeap)
{
	m_Data[i_Place].SetFlow(i_NewKey);
	while (i_Place != 0 && m_Data[Parent(i_Place)].GetCurrentFlow() < m_Data[i_Place].GetCurrentFlow())
	{
		int parentLocationInHeap = io_VerticesPlaceInTheHeap[m_Data[Parent(i_Place)].GetIndex()];
		int sontLocationInHeap = io_VerticesPlaceInTheHeap[m_Data[i_Place].GetIndex()];
		// update places in the auxiliary array
		io_VerticesPlaceInTheHeap[m_Data[i_Place].GetIndex()] = parentLocationInHeap;
		io_VerticesPlaceInTheHeap[m_Data[Parent(i_Place)].GetIndex()] = sontLocationInHeap;
		// swap elements in the heap
		Swap(&m_Data[i_Place], &m_Data[Parent(i_Place)]);
		i_Place = Parent(i_Place);
	}
}