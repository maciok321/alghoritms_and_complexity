#ifndef MENU_H
#define MENU_H

#include "Driver.h"
#include "Dijkstra.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"

#pragma once

class Menu
{
private:
    void displayMenu();

    void runDemoAdjacencyMatrix();
    void runDemoAdjacencyList();

    void runExperiment();

    void printDistances(const std::vector<int>& distances) const;

public:
    void runMenu();
    
};

#endif