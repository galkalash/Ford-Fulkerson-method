#include"Vertex.h"

Vertex::Vertex(int i_VertexIndex, int i_Weight)
{
    m_VertexIndex = i_VertexIndex;
    m_CurrentFlow = i_Weight;
}

int Vertex::GetCurrentFlow() // return the current flow to the vertex
{
    return m_CurrentFlow;
}

void Vertex::SetFlow(int i_NewFlow) // set current flow to vertex
{
    m_CurrentFlow = i_NewFlow;
}

void Vertex::SetIndex(int i_Index) // set index of the vertex in an array of vertices
{
    m_VertexIndex = i_Index;
}

int Vertex::GetIndex() // get the index of the vertex in an array of vertices
{
    return m_VertexIndex;
}