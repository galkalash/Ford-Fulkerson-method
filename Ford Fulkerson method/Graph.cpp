#include"Graph.h"
#include "Queue.h"
#include "MainUtilities.h"

Graph::Graph()
{
    m_AdjacencyMatrix = nullptr;
    m_NumberOfVertices = 0;
    m_NumberOfEdges = 0;
}

Graph::Graph(Graph& i_GraphToCopy) // Graph copy constructor
{
    m_NumberOfEdges = i_GraphToCopy.m_NumberOfEdges;
    m_NumberOfVertices = i_GraphToCopy.m_NumberOfVertices;
    m_AdjacencyMatrix = new int* [m_NumberOfVertices];
    for (int i = 0; i < m_NumberOfVertices; i++) // copy adjacency matrix values
    {
        m_AdjacencyMatrix[i] = new int[m_NumberOfVertices];
        for (int j = 0; j < m_NumberOfVertices; j++)
        {
             m_AdjacencyMatrix[i][j] = i_GraphToCopy.m_AdjacencyMatrix[i][j];
        }
    }
}

Graph::Graph(ifstream& i_graphParameters, int& o_StartingVertex, int& o_EndVertex)
{
    int numberOfEdges,sourceVertex, destinationVertex, edgeCapacity;
    char lineFromFile[MAX_LINE_SIZE], stringToConvertToInt[MAX_LINE_SIZE];
    List<int> edge;
    i_graphParameters.getline(lineFromFile, MAX_LINE_SIZE); // get number of vertices
    MainUtilities::CheckSingleNumberInput(lineFromFile); // validate input
    m_NumberOfVertices = atoi(lineFromFile);
    if (m_NumberOfVertices < 2) // check that there are at least 2 vertices
    {
        cout << "Invalid input" << endl;
        exit(1);
    }
    MakeEmptyGraph(m_NumberOfVertices); // initiate empty graph
    i_graphParameters.getline(lineFromFile, MAX_LINE_SIZE); // get number of edges
    MainUtilities::CheckSingleNumberInput(lineFromFile); // validate input
    numberOfEdges = atoi(lineFromFile);
    if (numberOfEdges < 0 || numberOfEdges >(m_NumberOfVertices * m_NumberOfVertices) - m_NumberOfVertices) 
        // check that the number of edges <= than n^2 - n (where n is the number of vertices)
    {
        cout << "Invalid input" << endl;
        exit(1);
    }
    i_graphParameters.getline(lineFromFile, MAX_LINE_SIZE); // get starting vertex
    MainUtilities::CheckSingleNumberInput(lineFromFile); // validate input
    o_StartingVertex = atoi(lineFromFile) - 1;
    i_graphParameters.getline(lineFromFile, MAX_LINE_SIZE); // get end vertex
    MainUtilities::CheckSingleNumberInput(lineFromFile); // validate input
    o_EndVertex = atoi(lineFromFile) - 1;
    if (o_StartingVertex + 1 > m_NumberOfVertices || o_EndVertex + 1 > m_NumberOfVertices) 
        // check that the start and end vertices are in range of the number of vertices
    {
        cout << "Invalid input" << endl;
        exit(1);
    }
    for (int i = 0; i < numberOfEdges; i++)
    {
        i_graphParameters.getline(lineFromFile, MAX_LINE_SIZE); // get an edge
        int k = 0;
        int index = 0;
        int startStr = 0;
        while (lineFromFile[k] == ' ' || lineFromFile[k] == '\t') // skip spaces at the beginning of the line
        {
            k++;
        }
        for (int j = k; j < (signed int)strlen(lineFromFile) + 1; j++)
        {
            if (lineFromFile[j] != ' ' && lineFromFile[j] != '\t' && lineFromFile[j] != '\0') 
                // insert the character to new string if is not space
            {
                stringToConvertToInt[index] = lineFromFile[j];
                index++;
            }
            else if ((lineFromFile[j] == ' ' || lineFromFile[j] == '\t' || lineFromFile[j] == '\0') && (lineFromFile[j - 1] != ' ' && lineFromFile[j - 1] != '\t'))// indicate that found a number
            {
                stringToConvertToInt[index] = '\0';
                MainUtilities::checkIfStringIsNumber(stringToConvertToInt); // validate input
                edge.AddNodeToTail(atoi(stringToConvertToInt)); // add the data to the list that represent an edge
                index = 0;
            }
        }
        if (edge.GetNumberOfNodes() != 3) // if the number of elements in a line is not 3 than exit the program
        {
            cout << "Invalid input" << endl;
            exit(1);
        }
        sourceVertex = edge.GetHead()->GetValue(); // first element represent the source vertex
        destinationVertex = edge.GetHead()->GetNext()->GetValue(); // second element represent the destination vertex
        edgeCapacity = edge.GetHead()->GetNext()->GetNext()->GetValue(); // third element represent the capacity of the edge
        if (sourceVertex > numberOfEdges || destinationVertex > numberOfEdges ||
            sourceVertex == destinationVertex || edgeCapacity < 0 || IsAdjacent(sourceVertex - 1, destinationVertex - 1))
            // check that the edge is not already in the graph, that there is no self loop, 
            //that the edge capacity > 0 and that the vertices are in range in the number of vertices
        {
            cout << "Invalid input" << endl;
            exit(1);
        }

        AddEdge(sourceVertex - 1, destinationVertex - 1, edgeCapacity);
        edge.MakeEmptyList();
    }
}

Graph::~Graph()
{
    for (int i = 0; i < m_NumberOfVertices; i++)
    {
        delete[] m_AdjacencyMatrix[i];
    }

    delete[] m_AdjacencyMatrix;
}

void Graph::MakeEmptyGraph(int i_NumberOfVertices) // initiate an empty graph with i_NumberOfVertices vertices
{
    m_NumberOfVertices = i_NumberOfVertices;
    m_AdjacencyMatrix = new int*[i_NumberOfVertices];
    for (int i = 0; i < i_NumberOfVertices; i++)
    {
        m_AdjacencyMatrix[i] = new int[i_NumberOfVertices];
        for (int j = 0; j < i_NumberOfVertices; j++)
        {
            m_AdjacencyMatrix[i][j] = 0;
        }
    }
}

bool Graph::IsAdjacent(int i_SourceVertex, int i_DestinationVertex) // checks if 2 vertices are adjacent
{
    return m_AdjacencyMatrix[i_SourceVertex][i_DestinationVertex] > 0;
}

List<int>* Graph::GetAdjList(int i_Vertex) // creates a list of the adjacents of i_Vertex
{
    List<int>* adjList = new List<int>;
    for (int i = 0; i < m_NumberOfVertices; i++)
    {
        if (m_AdjacencyMatrix[i_Vertex][i] > 0)
        {
            adjList->AddNodeToTail(i);
        }
    }

    return adjList;
}

void Graph::AddEdge(int i_SourceVertex, int i_DestinationVertex, int i_Capacity) 
// adds to the graph an edge between i_SourceVertex to i_DestinationVertex with the capacity of i_Capacity
{
    if (!IsAdjacent(i_SourceVertex,i_DestinationVertex))
    {
        m_AdjacencyMatrix[i_SourceVertex][i_DestinationVertex] = i_Capacity;
        m_NumberOfEdges++;
    }
}

void Graph::RemoveEdge(int i_SourceVertex, int i_DestinationVertex) // removes the edge between i_SourceVertex to i_DestinationVertex
{
    if (IsAdjacent(i_SourceVertex, i_DestinationVertex))
    {
        m_AdjacencyMatrix[i_SourceVertex][i_DestinationVertex] = 0;
        m_NumberOfEdges--;
    }
}

void Graph::BFS(int i_StartVertex, int*& o_DistanceArray, int*& o_ParentArray)
// runs BFS on the graph, returns distance array and parent array as output parameters
{
    Queue verticesQueue;
    int* distance = new int[m_NumberOfVertices]; // array for distance from starting vertex
    int* parent = new int[m_NumberOfVertices]; // array for parents of each vertex on the shortest path from the starting vertex
    int currentVertex;
    for (int i = 0; i < m_NumberOfVertices; i++) // initate arrays
    {
        distance[i] = INF;
        parent[i] = -1;
    }
    distance[i_StartVertex] = 0;
    verticesQueue.Enqueue(i_StartVertex);
    while (!verticesQueue.IsEmpty())
    {
        currentVertex = verticesQueue.Dequeue();
        for (int i = 0; i < m_NumberOfVertices; i++)
        {
            if (m_AdjacencyMatrix[currentVertex][i] != 0 && distance[i] == INF) // update arrayes
            {
                distance[i] = distance[currentVertex] + 1;
                parent[i] = currentVertex;
                verticesQueue.Enqueue(i);
            }
        }
    }

    o_DistanceArray = distance;
    o_ParentArray = parent;
}

void Graph::SetNumberOfEdges(int i_NumberOfEdges) // sets the number of endges in the graph
{
    m_NumberOfEdges = i_NumberOfEdges;
}

int Graph::FindMinimumPathCapacity(int i_StartingVertex, int i_EndVertex, int* i_ParentArray)
// returns the capacity of the shortest path between i_StartingVertex to i_EndVertex
{
    // initiate the result with the capacity of the edge between the parent of the end vertex to the end vertex
    int minimumCapacity = m_AdjacencyMatrix[i_ParentArray[i_EndVertex]][i_EndVertex]; 
    int currentVertex = i_ParentArray[i_EndVertex];
    // scan the path using the parent array
    while (currentVertex != i_StartingVertex)
    {
        if (minimumCapacity > m_AdjacencyMatrix[i_ParentArray[currentVertex]][currentVertex])
        {
            minimumCapacity = m_AdjacencyMatrix[i_ParentArray[currentVertex]][currentVertex];
        }

        currentVertex = i_ParentArray[currentVertex];
    }

    return minimumCapacity;
}

void Graph::UpdateResidualGraphCapacity(int i_StartingVertex, int i_EndVertex, int* i_ParentArray, int i_Flow)
// update the capacity of each edge on the path from i_StartingVertex to i_EndVertex 
{
    int currentVertex = i_EndVertex;
    while (i_StartingVertex != currentVertex)
    {
        // subtract i_Flow from each edge on the path from i_StartingVertex to i_EndVertex
        m_AdjacencyMatrix[i_ParentArray[currentVertex]][currentVertex] -= i_Flow;
        // add i_Flow from each edge on the path from i_EndVertex to i_StartingVertex
        m_AdjacencyMatrix[currentVertex][i_ParentArray[currentVertex]] += i_Flow;
        currentVertex = i_ParentArray[currentVertex];
    }
}

void Graph::GetMinimumCut(int i_StartingIndex,List<int>& io_SSet, List<int>& io_TSet)
{
    // finds min cut of the graph with max flow, and returns S set and T set as output parameters
    int *distance, *parent;
    BFS(i_StartingIndex, distance, parent);
    for (int i = 0; i < m_NumberOfVertices; i++)
    {
        if (distance[i] != -1)
        {
            io_SSet.AddNodeToTail(i + 1);
        }
        else
        {
            io_TSet.AddNodeToTail(i + 1);
        }
    }
    delete[] distance;
    delete[] parent;
}

Vertex* Graph::DijkstraVariationForMaxFlow(int i_StartinVertex, int*& o_ParentArray)
// finds the path which can stream the most from i_StartinVertex to each vertex
{
    PriorityMaxQueue maxQueue;
    Vertex currentVertex;
    Vertex* verticesArrayForMaxQueue = buildVerticesArray(); // array for the priority queue
    Vertex* verticesArray = buildVerticesArray(); // array for the current function
    int* verticesPlaceInTheHeap = new int[m_NumberOfVertices]; // an auxiliary array which represent the index of each vertex in the array of priority queue
    o_ParentArray = new int[m_NumberOfVertices];
    for (int i = 0; i < m_NumberOfVertices; i++)
    {
        verticesPlaceInTheHeap[i] = i;
        o_ParentArray[i] = -1;
    }
    // set the current flow to the starting index as INF (in order to delete it first from the priority queue)
    verticesArray[i_StartinVertex].SetFlow(INF);
    verticesArrayForMaxQueue[i_StartinVertex].SetFlow(INF);

    maxQueue.Build(verticesArrayForMaxQueue, m_NumberOfVertices, verticesPlaceInTheHeap); // build the priority queue
    while (!maxQueue.IsEmpty())
    {
        currentVertex = maxQueue.DeleteMax(verticesPlaceInTheHeap);
        for (int i = 0; i < m_NumberOfVertices; i++)
        {
            if (verticesPlaceInTheHeap[i] >= 0 && this->IsAdjacent(currentVertex.GetIndex(), i))
            {
                // check if needed to update the flow to a vertex if it is an adjacent of the current vertex and it is still in the priority queue
                Relax(verticesArray[currentVertex.GetIndex()], verticesArray[i], maxQueue, o_ParentArray, verticesPlaceInTheHeap);
            }
        }
    }

    delete[]verticesPlaceInTheHeap;
    delete[]verticesArrayForMaxQueue;
    return verticesArray;
}

void Graph::Relax(Vertex& i_SourceVertex, Vertex& i_DestinationVertex, PriorityMaxQueue& i_MaxQueue, int* i_ParentArray, int* io_VerticesPlaceInTheHeap)
{
    int minimumFlow;
    if (i_SourceVertex.GetCurrentFlow() == INF || i_SourceVertex.GetCurrentFlow() > m_AdjacencyMatrix[i_SourceVertex.GetIndex()][i_DestinationVertex.GetIndex()])
    {
        // set the minimumFlow as the edge capacity between i_SourceVertex to i_DestinationVertex if i_SourceVertex is the starting vertex or the current flow to the sourceVertex > from the edge capacity
        minimumFlow = m_AdjacencyMatrix[i_SourceVertex.GetIndex()][i_DestinationVertex.GetIndex()];
    }
    else
    {
        // else set minimumFlow as the sourceVertex flow
        minimumFlow = i_SourceVertex.GetCurrentFlow();
    }
    if (i_DestinationVertex.GetCurrentFlow() < minimumFlow)
    {
        // update i_DestinationVertex flow to minimumFlow
        i_DestinationVertex.SetFlow(minimumFlow);
        // subtract minimumFlow from the edge capacity from i_SourceVertex to i_DestinationVertex on the residual graph
        m_AdjacencyMatrix[i_SourceVertex.GetIndex()][i_DestinationVertex.GetIndex()] -= minimumFlow;
        // add minimumFlow to the edge capacity from i_DestinationVertex to i_SourceVertex on the residual graph
        m_AdjacencyMatrix[i_DestinationVertex.GetIndex()][i_SourceVertex.GetIndex()] += minimumFlow;
        // update i_DestinationVertex parent to i_SourceVertex
        i_ParentArray[i_DestinationVertex.GetIndex()] = i_SourceVertex.GetIndex();
        // increase the key of i_DestinationVertex in the priority queue
        i_MaxQueue.IncreaseKey(io_VerticesPlaceInTheHeap[i_DestinationVertex.GetIndex()] , i_DestinationVertex.GetCurrentFlow(), io_VerticesPlaceInTheHeap);
    }
}

Vertex* Graph::buildVerticesArray()
{
    Vertex* resultArray = new Vertex[m_NumberOfVertices];
    for (int i = 0; i < m_NumberOfVertices; i++)
    {
        resultArray[i].SetIndex(i);
        resultArray[i].SetFlow(0); // initiate each vertex flow to 0
    }

    return resultArray;
}

int Graph::GetNumberOfVertices() // return the number of vertices of the graph
{
    return m_NumberOfVertices;
}