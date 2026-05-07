#include "AdjacencyMatrixGraph.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int numVertices) : numVertices(numVertices)
{
    adjMatrix = std::vector<std::vector<int>>(numVertices, std::vector<int>(numVertices, NO_EDGE));
}

int AdjacencyMatrixGraph::getNumVertices() const
{
    return numVertices;
}

int AdjacencyMatrixGraph::getWeight(int u, int v) const
{
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        throw std::out_of_range("Vertex index out of range");

    if(!hasEdge(u, v))
        throw std::runtime_error("No edge exists between the specified vertices");
    return adjMatrix[u][v];
}

bool AdjacencyMatrixGraph::hasEdge(int u, int v) const
{
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        throw std::out_of_range("Vertex index out of range");
    return adjMatrix[u][v] != NO_EDGE;
}

void AdjacencyMatrixGraph::printGraph() const
{
    for (int i = 0; i < numVertices; ++i)
    {
        for (int j = 0; j < numVertices; ++j)
        {
            if (adjMatrix[i][j] != NO_EDGE)
                std::cout << "Edge from " << i << " to " << j << " with weight " << adjMatrix[i][j] << std::endl;
        }
    }
}

void AdjacencyMatrixGraph::addEdge(int u, int v, int weight)
{
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        throw std::out_of_range("Vertex index out of range");

    if(weight <= 0)
        throw std::invalid_argument("Weight must be a positive integer");
    
    adjMatrix[u][v] = weight;
}

std::vector<std::pair<int, int>> AdjacencyMatrixGraph::getNeighbors(int vertex) const
{
    if (vertex < 0 || vertex >= numVertices)
        throw std::out_of_range("Vertex index out of range");

    std::vector<std::pair<int, int>> neighbors;
    for (int j = 0; j < numVertices; ++j)
    {
        if (adjMatrix[vertex][j] != NO_EDGE)
            neighbors.emplace_back(j, adjMatrix[vertex][j]);
    }
    return neighbors;
}
