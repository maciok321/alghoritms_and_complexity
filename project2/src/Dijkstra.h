#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#pragma once
#include "Graph.h"
#include <vector>
#include <limits>
#include <queue>
#include <stdexcept>
#include <functional>

class Dijkstra
{
public:
    // Obliczanie najkrótszych odległości od startVertex do wszystkich wierzchołków.
    // Wierzchołki nieosiągalne zachowują wartość INF.
    static std::vector<int> findShortestPath(const Graph& graph, int startVertex);

private:
    // Wartość oznaczająca brak dotarcia do wierzchołka.
    static constexpr int INF = std::numeric_limits<int>::max();
};

#endif