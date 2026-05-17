#include "Driver.h"

Driver::Driver() : vertexCounts{10, 50, 100, 500, 1000},
    densities{0.25, 0.5, 0.75, 1.0},
    graphTypes{GraphType::AdjacencyMatrix, GraphType::AdjacencyList},
    numOfTrials(100),
    outputFileName("results.csv")
{} 

void Driver::run()
{
    // nowy raport od nadpisania pliku i zapisu nagłówka.
    saveHeader();

    for (GraphType graphType : graphTypes)
    {
        for (int numVertices : vertexCounts)
        {
            for (double density : densities)
            {
                double avgTime = runSingleTrial(numVertices, density, graphType);
                saveResults("Dijkstra", graphTypeToString(graphType), numVertices, density, avgTime);
            }
        }
    }
}

double Driver::runSingleTrial(int numVertices, double density, GraphType graphType)
{
    double totalTime = 0.0;
    std::vector<std::unique_ptr<Graph>> graphs;
    graphs.reserve(numOfTrials);
    // Generacja danych wejściowych

    for (int i = 0; i < numOfTrials; ++i)
    {
        graphs.push_back(GraphGenerator::generateRandomGraph(numVertices, density, graphType));
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < numOfTrials; ++i)
    {
        auto distances = Dijkstra::findShortestPath(*graphs[i], 0);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    return totalTime / numOfTrials;
}

void Driver::saveHeader() const
{
    std::ofstream outFile(outputFileName);
    if (outFile.is_open())
    {
        outFile << "Algorithm,GraphType,NumVertices,Density,AverageTimeNanoseconds\n";
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << outputFileName << std::endl;
    }
}

void Driver::saveResults(const std::string& algoName, const std::string& graphTypeName, int numVertices, double density, double timeTaken) const
{
    std::ofstream outFile(outputFileName, std::ios_base::app);
    if (outFile.is_open())
    {
        outFile << algoName << "," << graphTypeName << "," << numVertices << "," << density << "," << timeTaken << "\n";
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << outputFileName << std::endl;
    }
}

std::string Driver::graphTypeToString(GraphType graphType) const
{
    switch (graphType)
    {
    case GraphType::AdjacencyMatrix:
        return "AdjacencyMatrix";
    case GraphType::AdjacencyList:
        return "AdjacencyList";
    default:
        return "UnknownGraphType";
    }
}

