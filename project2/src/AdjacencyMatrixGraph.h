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
    int numVertices; // Liczba wierzchołków w grafie skierowanym.
    std::vector<std::vector<int>> adjMatrix; // Macierz wag indeksowana jako [z][do].
    static constexpr int NO_EDGE = 0; // Wartość oznaczająca brak krawędzi.

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