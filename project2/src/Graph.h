#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#pragma once

class Graph
{
public:
    virtual ~Graph() = default;

    // Zwraca liczbę wierzchołków w grafie.
    virtual int getNumVertices() const = 0;
    // Zwraca wagę krawędzi skierowanej u -> v lub zgłasza wyjątek, gdy krawędź nie istnieje.
    virtual int getWeight(int u, int v) const = 0;
    // Sprawdza, czy istnieje krawędź skierowana u -> v.
    virtual bool hasEdge(int u, int v) const = 0;
    // Wypisuje wszystkie krawędzie przechowywane przez daną reprezentację grafu.
    virtual void printGraph() const = 0;
    // Dodaje nową krawędź lub aktualizuje wagę istniejącej krawędzi u -> v.
    virtual void addEdge(int u, int v, int weight) = 0;
    
    // Zwraca listę sąsiadów wychodzących jako pary (wierzchołek, waga).
    virtual std::vector<std::pair<int,int>> getNeighbors(int vertex) const = 0;
};

#endif