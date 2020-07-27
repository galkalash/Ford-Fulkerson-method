#include "MainUtilities.h"

void MainUtilities::PrintResults(Graph& i_ResidualGraph, List<int>& i_SList, List<int>& i_TList,int i_MaxFlow, int i_NumberOfIterations)
{
    cout << "==================================" << endl;
    cout << "Max flow = " << i_MaxFlow << endl;
    cout << "Min cut: S= ";
    ListNode<int>* tempNode = i_SList.GetHead();
    while (tempNode != nullptr) // print S set
    {
        cout << tempNode->GetValue() << " ";
        tempNode = tempNode->GetNext();
    }
    cout << " T= ";
    tempNode = i_TList.GetHead();
    while (tempNode != nullptr) // print T set
    {
        cout << tempNode->GetValue() << " ";
        tempNode = tempNode->GetNext();
    }

    cout << endl << "number of iterations = " << i_NumberOfIterations << endl;
    cout << "==================================" << endl;
}


void MainUtilities::RunFordFulkersonWithDijkstra(Graph& i_Graph, int i_StartingVertex, int i_EndVertex)
{
    int maxFlow = 0, numberOfIterations = 0, pathFlow;
    Graph* residualGraph = new Graph(i_Graph); // holds the residual graph
    Graph* residualGraphCopy = new Graph(*residualGraph);// holds a copy of the residual graph for Dijkstra algorithm for max flow
    int* parentArray; // holds the current parent array after Dijkstra run
    Vertex* verticesAfterDijkstra; // holds the vertices array that returns from Dijkstra
    verticesAfterDijkstra = residualGraphCopy->DijkstraVariationForMaxFlow(i_StartingVertex, parentArray);
    // this loop is running while there is a path from the starting vertex to the end vertex in the residual graph
    while (verticesAfterDijkstra[i_EndVertex].GetCurrentFlow() > 0)
    {
        numberOfIterations++;
        pathFlow = verticesAfterDijkstra[i_EndVertex].GetCurrentFlow(); // gets the flow that reached to the end vertex
        maxFlow += pathFlow; // add this flow to max flow
        residualGraph->UpdateResidualGraphCapacity(i_StartingVertex, i_EndVertex, parentArray, pathFlow); // update the residual graph edges capacity after streaming
        delete[]parentArray;
        delete residualGraphCopy;
        delete[]verticesAfterDijkstra;
        residualGraphCopy = new Graph(*residualGraph); // create a copy of the updated residual graph
        verticesAfterDijkstra = residualGraphCopy->DijkstraVariationForMaxFlow(i_StartingVertex, parentArray); // run Dijkstra again
    }
    delete residualGraphCopy;
    delete[]parentArray;
    delete verticesAfterDijkstra; 

    List<int> SList, TList;
    residualGraph->GetMinimumCut(i_StartingVertex, SList, TList); // find min cut
    cout << "Greedy Method:" << endl;
    PrintResults(*residualGraph, SList, TList, maxFlow, numberOfIterations); // print the results
    SList.MakeEmptyList();
    TList.MakeEmptyList();
    delete residualGraph;
}

void MainUtilities::RunFordFulkersonWithBFS(Graph& i_Graph, int i_StartingVertex, int i_EndVertex)
{
    int maxFlow = 0, numberOfIterations = 0, pathFlow;
    int* distanceArray, * parentArray;
    Graph* residualGraph = new Graph(i_Graph);
    residualGraph->BFS(i_StartingVertex, distanceArray, parentArray); // find the shortest path from i_StartingVertex to each vertex on the graph
    // this loop runs while there is a path from i_StartingVertex to i_EndVertex
    while (distanceArray[i_EndVertex] != INF)
    {
        numberOfIterations++;
        pathFlow = residualGraph->FindMinimumPathCapacity(i_StartingVertex, i_EndVertex, parentArray); // get the flow of the shortest path from i_StartingVertex to i_EndVertex
        maxFlow += pathFlow; // add the flow to the max flow
        residualGraph->UpdateResidualGraphCapacity(i_StartingVertex, i_EndVertex, parentArray, pathFlow); // update the residual graph with the flow that streamed
        delete[] distanceArray;
        delete[] parentArray;
        residualGraph->BFS(i_StartingVertex, distanceArray, parentArray); // find the shortest path from i_StartingVertex to each vertex on the graph again
    }
    delete[] distanceArray;
    delete[] parentArray;
    List<int> SList, TList;
    residualGraph->GetMinimumCut(i_StartingVertex, SList, TList); // get the min cut
    cout << "BFS Method:" << endl;
    PrintResults(*residualGraph, SList, TList, maxFlow, numberOfIterations); // print the results
    SList.MakeEmptyList();
    TList.MakeEmptyList();
    delete residualGraph;
}

void MainUtilities::checkIfStringIsNumber(char* i_String)
{
    int i = 0;
    while (i_String[i] != '\0')
    {
        if (i_String[i] < '0' || i_String[i] > '9') // check if each character of the string is a digit
        {
            cout << "Invalid input" << endl;
            exit(1);
        }
        i++;
    }
}

void MainUtilities::CheckSingleNumberInput(char* i_LineFromFile)
{
    int k = 0;
    int index = 0;
    char stringToReturn[MAX_LINE_SIZE], stringToConvertToInt[MAX_LINE_SIZE];
    bool stringIsUpdate = false;
    while (i_LineFromFile[k] == ' ' || i_LineFromFile[k] == '\t') // cehck if there are spaces before the string
    {
        k++;
    }
    for (int j = k; j < (signed int)strlen(i_LineFromFile) + 1; j++)
    {
        if (i_LineFromFile[j] != ' ' && i_LineFromFile[j] != '\t' && i_LineFromFile[j] != '\0') // checks if the character is not space or end of line
        {
            stringToConvertToInt[index] = i_LineFromFile[j]; // adds the character to the result string
            index++;
        }
        else if ((i_LineFromFile[j] == ' ' || i_LineFromFile[j] == '\t' || i_LineFromFile[j] == '\0') && (i_LineFromFile[j - 1] != ' ' && i_LineFromFile[j - 1] != '\t'))
        // checks if finished reading a stirng
        {
            if (stringIsUpdate == false && index > 0) // check that there is a single string in the line
            {
                stringToConvertToInt[index] = '\0';
                checkIfStringIsNumber(stringToConvertToInt);
                strcpy(stringToReturn, stringToConvertToInt);
                stringIsUpdate = true;
            }
            else // there are couple of strings in the line
            {
                cout << "Invalid input" << endl;
                exit(1);
            }
        }
    }

	strcpy(i_LineFromFile, stringToReturn);
}