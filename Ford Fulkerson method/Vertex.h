#pragma once
#define INF -1

class Vertex
{
private:
    int m_VertexIndex;
    int m_CurrentFlow;
public:
    Vertex() = default;
    Vertex(int i_VertexIndex, int i_Weight);
    int GetCurrentFlow();
    void SetFlow(int i_NewFlow);
    void SetIndex(int i_Index);
    int GetIndex();
};