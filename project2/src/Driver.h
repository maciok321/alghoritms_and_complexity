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
    // Zestawy parametrów używane do generowania konfiguracji testowych.
    std::vector<int> vertexCounts;
    std::vector<double> densities;
    std::vector<GraphType> graphTypes;

    int numOfTrials; // Liczba losowych grafów dla każdej konfiguracji.
    std::string outputFileName; // Plik CSV z wynikami eksperymentów.

    // Uruchomienie pojedynczej konfiguracji i zwracanie średniego czasu w nanosekundach.
    double runSingleTrial(int numVertices, double density, GraphType graphType);

    // Tworzenie nowego pliku wynikowego i zapisanie nagłówka kolumn.
    void saveHeader() const;
    // Dopisanie jednego wiersza z wynikiem do pliku CSV.
    void saveResults(const std::string& algoName, const std::string& graphType, int numVertices, double density, double timeTaken) const;

    // Zamiana typu grafu na tekst używany w raporcie.
    std::string graphTypeToString(GraphType graphType) const;
    
public:
    Driver();

    // Wykonanie pełnej siatki eksperymentów.
    void run();
};

#endif
