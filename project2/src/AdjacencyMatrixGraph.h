#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H

#pragma once
#include "Graph.h"
#include <vector>
#include <stdexcept>
#include <iostream>

class AdjacencyMatrixGraph : public Graph
{
private:
    int numVertices;
    std::vector<std::vector<int>> adjMatrix;
    static constexpr int NO_EDGE = 0; // Sentinel value for no edge

public:
    explicit AdjacencyMatrixGraph(int numVertices);

    int getNumVertices() const override;
    int getWeight(int u, int v) const override;
    bool hasEdge(int u, int v) const override;
    void printGraph() const override;

    void addEdge(int u, int v, int weight) override;
    std::vector<std::pair<int, int>> getNeighbors(int vertex) const override;

};

#endif