#ifndef DRIVER_H
#define DRIVER_H

#include "GraphGenerator.h"
#include "Dijkstra.h"
#include <fstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

#pragma once

class Driver
{
private:
    std::vector<int> vertexCounts;
    std::vector<double> densities;
    std::vector<GraphType> graphTypes;

    int numOfTrials;
    std::string outputFileName;

    double runSingleTrial(int numVertices, double density, GraphType graphType);

    void saveHeader() const;
    void saveResults(const std::string& algoName, const std::string& graphType, int numVertices, double density, double timeTaken) const;

    std::string graphTypeToString(GraphType graphType) const;
    
public:
    Driver();

    void run();
};

#endif