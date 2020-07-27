#pragma once
#include "ListNode.h"
template <class T>
class List
{
private:
    ListNode<T>* m_Head;
    ListNode<T>* m_Tail;
    int m_NumberOfNodes;

public:
    List()
    {
        m_Head = nullptr;
        m_Tail = nullptr;
        m_NumberOfNodes = 0;
    }
    ~List()
    {
        ListNode<T>* currentNode = m_Head;
        while (currentNode != nullptr) // delete each node in the list
        {
            currentNode = m_Head->GetNext();
            delete m_Head;
        }
    }
    ListNode<T>* GetHead() // returns the head of the list
    {
        return m_Head;
    }
    ListNode<T>* GetTail() // returns the tail of the list
    {
        return m_Tail;
    }
    void AddNodeToTail(T i_Value) // adds node to the tail of the list
    {
        if (m_Tail == nullptr)
        {
            m_Head = new ListNode<T>(i_Value);
            m_Tail = m_Head;
        }
        else
        {
            ListNode<T>* newTail = new ListNode<T>(i_Value);
            m_Tail->SetNext(newTail);
            m_Tail = newTail;
        }

        m_NumberOfNodes++;
    }
    void MakeEmptyList() // delete each node of the list and initiate it as empty list
    {
        while (m_Head != nullptr)
        {
            DeleteHead();
        }
        m_Head = m_Tail = nullptr;
        m_NumberOfNodes = 0;
    }
    void SetHead(ListNode<T>* m_NewHead) // set the head of the list
    {
        m_Head = m_NewHead;
    }
    void SetTail(ListNode<T>* m_NewTail) // set the tail of the list
    {
        m_Tail = m_NewTail;
    }
    void DeleteHead() // deletes the head of the list
    {
        if (m_Head == m_Tail)
        {
            m_Tail = nullptr;
            delete m_Head;
            m_Head = nullptr;
        }
        else
        {
            ListNode<T>* tempNode = m_Head;
            m_Head = m_Head->GetNext();
            delete tempNode;
        }
        m_NumberOfNodes--;
    }
    int GetNumberOfNodes() // returns the number of nodes in the list
    {
        return m_NumberOfNodes;
    }
};