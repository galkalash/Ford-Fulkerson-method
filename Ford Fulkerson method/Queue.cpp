#include "Queue.h"

Queue::~Queue()
{
    MakeEmpty();
}

void Queue::MakeEmpty()
{
    m_Items.MakeEmptyList();
}

bool Queue::IsEmpty() // checks if the queue is empty
{
    return m_Items.GetHead() == nullptr && m_Items.GetTail() == nullptr;
}

void Queue::Enqueue(int i_Value) // insert new data to the queue
{
	m_Items.AddNodeToTail(i_Value);
}

int Queue::Dequeue() // return and remove the head of the queue
{
    int result = m_Items.GetHead()->GetValue();
	m_Items.DeleteHead();
    return result;
}