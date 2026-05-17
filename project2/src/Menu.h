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
    // Wyświetla dostępne opcje dla użytkownika.
    void displayMenu();
    
    // Pokaz działania algorytmu na grafie w reprezentacji macierzy sąsiedztwa.
    void runDemoAdjacencyMatrix();
    // Pokaz działania algorytmu na grafie w reprezentacji listy sąsiedztwa.
    void runDemoAdjacencyList();
    // Uruchamia serię eksperymentów wydajnościowych.
    void runExperiment();
    
    // Wypisuje odległości od wierzchołka źródłowego do wszystkich wierzchołków.
    void printDistances(const std::vector<int>& distances) const;

public:
    // Główna pętla interaktywnego menu.
    void runMenu();
    
};

#endif