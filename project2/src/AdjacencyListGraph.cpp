#include "AdjacencyListGraph.h"

AdjacencyListGraph::AdjacencyListGraph(int numVertices) : numVertices(numVertices)
{
    adjList = std::vector<std::vector<std::pair<int, int>>>(numVertices);
}

int AdjacencyListGraph::getNumVertices() const
{
    return numVertices;
}

int AdjacencyListGraph::getWeight(int u, int v) const
{
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        throw std::out_of_range("Vertex index out of range");
    // Przeszukanie krawędzi wychodzących z u, aby znaleźć krawędź u -> v.

    for (const auto& neighbor : adjList[u])
    {
        if (neighbor.first == v)
            return neighbor.second;
    }
    throw std::runtime_error("No edge exists between the specified vertices");
}

bool AdjacencyListGraph::hasEdge(int u, int v) const
{
    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        throw std::out_of_range("Vertex index out of range");

    for (const auto& neighbor : adjList[u])
    {
        if (neighbor.first == v)
            return true;
    }
    return false;
}

void AdjacencyListGraph::printGraph() const
{
    for (int i = 0; i < numVertices; ++i)
    {
        for (const auto& neighbor : adjList[i])
        {
            std::cout << "Edge from " << i << " to " << neighbor.first << " with weight " << neighbor.second << std::endl;
        }
    }
}

void AdjacencyListGraph::addEdge(int u, int v, int weight)

{

    if (u < 0 || u >= numVertices || v < 0 || v >= numVertices)
        throw std::out_of_range("Vertex index out of range");
        
    if (weight <= 0)
        throw std::invalid_argument("Weight must be a positive integer");

    for (auto& neighbor : adjList[u])
    {
        if (neighbor.first == v)
        {
            // aktualizacja wagi istniejącej krawędzi u -> v
            neighbor.second = weight;

            return;
        }
    }
    // jeśli krawędzi nie było, dodaje nową parę (sąsiad, waga).
    adjList[u].emplace_back(v, weight);
}

std::vector<std::pair<int, int>> AdjacencyListGraph::getNeighbors(int vertex) const
{
    if (vertex < 0 || vertex >= numVertices)
        throw std::out_of_range("Vertex index out of range");

    return adjList[vertex];
}
