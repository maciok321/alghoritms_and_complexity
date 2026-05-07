#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#pragma once

class Graph
{
public:
    virtual ~Graph() = default;

    virtual int getNumVertices() const = 0;
    virtual int getWeight(int u, int v) const = 0;
    virtual bool hasEdge(int u, int v) const = 0;
    virtual void printGraph() const = 0;

    virtual void addEdge(int u, int v, int weight) = 0;
    
    virtual std::vector<std::pair<int,int>> getNeighbors(int vertex) const = 0;
};

#endif