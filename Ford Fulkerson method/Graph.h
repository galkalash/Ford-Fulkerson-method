#pragma once
#include "List.h"
#include "PriorityMaxQueue.h"
#include "Vertex.h"
#include <fstream>


class Graph
{
private:
    int m_NumberOfEdges;
    int m_NumberOfVertices;
    int** m_AdjacencyMatrix;

public:
    Graph();
    Graph(Graph& i_GraphToCopy);
    Graph(ifstream& i_graphParameters, int& o_StartingVertex, int& o_EndVertex);
    ~Graph();
    void SetNumberOfEdges(int i_NumberOfEdges);
    int GetNumberOfVertices();
    void MakeEmptyGraph(int i_NumberOfVertices);
    bool IsAdjacent(int i_SourceVertex, int i_DestinationVertex);
    List<int>* GetAdjList(int i_Vertex);
    void AddEdge(int i_SourceVertex, int i_DestinationVertex, int i_Capacity);
    void RemoveEdge(int i_SourceVertex, int i_DestinationVertex);
    void BFS(int i_StartVertex, int*& o_DistanceArray, int*& o_ParentArray);
    int FindMinimumPathCapacity(int i_StartingVertex, int i_EndVertex, int* i_ParentArray);
    void UpdateResidualGraphCapacity(int i_StartingVertex, int i_EndVertex, int* i_ParentArray, int i_Flow);
    void GetMinimumCut(int i_StartingIndex, List<int>& io_SSet, List<int>& io_TSet);
    Vertex* DijkstraVariationForMaxFlow(int i_StartinVertex, int*& o_ParentArray);
    Vertex* buildVerticesArray();
    void Relax(Vertex& i_SourceVertex, Vertex& i_DestinationVertex, PriorityMaxQueue& i_MaxQueue, int* i_ParentArray, int* io_VerticesPlaceInTheHeap);
};