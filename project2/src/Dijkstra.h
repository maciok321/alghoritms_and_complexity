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
    static std::vector<int> findShortestPath(const Graph& graph, int startVertex);

private:
    static constexpr int INF = std::numeric_limits<int>::max();
};

#endif