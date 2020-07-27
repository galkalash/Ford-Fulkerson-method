#pragma once
template <class T>
class ListNode 
{
private:
    T m_Value;
    ListNode* m_Next;

public:
    ListNode(T i_Value)
    {
        m_Value = i_Value;
        m_Next = nullptr;
    }
    void SetNext(ListNode<T>* i_NextNode) // set node`s next
    {
        m_Next = i_NextNode;
    }
    ListNode* GetNext() // returns node`s next
    {
        return m_Next;
    }
    T GetValue() // returns node`s value
    {
        return m_Value;
    }
};