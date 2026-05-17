#ifndef ADJACENCYLISTGRAPH_H
#define ADJACENCYLISTGRAPH_H

#pragma once
#include "Graph.h"
#include <vector>
#include <stdexcept>
#include <iostream>

class AdjacencyListGraph : public Graph
{
private:
    int numVertices; // Liczba wierzchołków w grafie skierowanym.
    std::vector<std::vector<std::pair<int, int>>> adjList; // Dla każdego wierzchołka: para <sąsiad, waga>.

public:
    explicit AdjacencyListGraph(int numVertices);

    int getNumVertices() const override;
    int getWeight(int u, int v) const override;
    bool hasEdge(int u, int v) const override;
    void printGraph() const override;

    void addEdge(int u, int v, int weight) override;
    std::vector<std::pair<int, int>> getNeighbors(int vertex) const override;

};

#endif