#include "GraphGenerator.h"

std::unique_ptr<Graph> GraphGenerator::generateRandomGraph(int numVertices, double density, GraphType graphType)
{
    if (numVertices <= 0)
        throw std::invalid_argument("Number of vertices must be greater than zero.");

    if (density < 0.0 || density > 1.0)
        throw std::invalid_argument("Density must be between 0 and 1.");

    std::unique_ptr<Graph> graph;

    switch (graphType)
    {
    case GraphType::AdjacencyMatrix:
        graph = std::make_unique<AdjacencyMatrixGraph>(numVertices);
        break;
    case GraphType::AdjacencyList:
        graph = std::make_unique<AdjacencyListGraph>(numVertices);
        break;
    default:
        throw std::invalid_argument("Invalid graph type.");
    }

    int numEdges = calculateNumEdges(numVertices, density);
    int addedEdges = 0;

    if (density >= 1.0)
    {
        // For a complete graph, add all possible edges
        for (int u = 0; u < numVertices; ++u)
        {
            for (int v = 0; v < numVertices; ++v)
            {
                if (u != v)
                {
                    int weight = generateRandomWeight();
                    graph->addEdge(u, v, weight);
                }
            }
        }
        return graph;
    }

    while (addedEdges < numEdges)
    {
        int u = generateRandomVertex(numVertices);
        int v = generateRandomVertex(numVertices);

        if (u == v || graph->hasEdge(u, v))
            continue; // Skip self-loops and duplicate edges

        graph->addEdge(u, v, generateRandomWeight());
        addedEdges++;
    }

    return graph;
}

int GraphGenerator::calculateMaxEdges(int numVertices)
{
    return (numVertices * (numVertices - 1)); // For directed graph
}

int GraphGenerator::calculateNumEdges(int numVertices, double density)
{
    int maxEdges = calculateMaxEdges(numVertices);
    return static_cast<int>(std::round(maxEdges * density));
}

int GraphGenerator::generateRandomVertex(int numVertices)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, numVertices - 1);
    return dis(gen);
}

int GraphGenerator::generateRandomWeight(int minWeight, int maxWeight)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minWeight, maxWeight);
    return dis(gen);
}