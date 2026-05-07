#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include "Graph.h"
#include "AdjacencyMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include <vector>
#include <random>
#include <stdexcept>
#include <memory>
#include <cmath>

#pragma once

enum class GraphType
{
    AdjacencyMatrix,
    AdjacencyList
};

class GraphGenerator
{
public:
    static std::unique_ptr<Graph> generateRandomGraph(int numVertices, double density, GraphType graphType);
private:
    static const int MIN_WEIGHT = 1;
    static const int MAX_WEIGHT = 100;

    static int calculateMaxEdges(int numVertices);
    static int calculateNumEdges(int numVertices, double density);

    static int generateRandomVertex(int numVertices);
    static int generateRandomWeight(int minWeight = MIN_WEIGHT, int maxWeight = MAX_WEIGHT);
};

#endif