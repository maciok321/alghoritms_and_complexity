#include "Dijkstra.h"

std::vector<int> Dijkstra::findShortestPath(const Graph& graph, int startVertex)

{
    int numVertices = graph.getNumVertices();
    
    if (startVertex < 0 || startVertex >= numVertices)
        throw std::out_of_range("Start vertex index out of range");

    std::vector<int> distances(numVertices, INF);

    using QueueElement = std::pair<int, int>;

    // first  = aktualna odległość
    // second = numer wierzchołka

    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> priorityQueue;

    distances[startVertex] = 0;

    priorityQueue.push({0, startVertex});

    while (!priorityQueue.empty())
    {
        int currentDistance = priorityQueue.top().first;
        int u = priorityQueue.top().second;

        priorityQueue.pop();

        if (currentDistance > distances[u])
            continue;

        for (const auto& neighbor : graph.getNeighbors(u))
        {

            int v = neighbor.first;
            int weight = neighbor.second;

            if (distances[u] != INF && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;

                priorityQueue.push({distances[v], v});
            }
        }
    }
    return distances;
}