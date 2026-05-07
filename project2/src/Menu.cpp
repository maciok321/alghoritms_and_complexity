#include "Menu.h"

void Menu::runMenu()
{
    int choice = 0;
    while (choice != 4)
    {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                runDemoAdjacencyMatrix();
                break;
            case 2:
                runDemoAdjacencyList();
                break;
            case 3:
                runExperiment();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void Menu::displayMenu()
{
    std::cout << "Menu Options:" << std::endl;
    std::cout << "1. Run Dijkstra's Algorithm (Adjacency Matrix)" << std::endl;
    std::cout << "2. Run Dijkstra's Algorithm (Adjacency List)" << std::endl;
    std::cout << "3. Run Experiment" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void Menu::printDistances(const std::vector<int>& distances) const
{
    for (int i = 0; i < static_cast<int>(distances.size()); ++i)
    {
        std::cout << "Source -> " << i << ": ";

        if (distances[i] == std::numeric_limits<int>::max())
            std::cout << "Vertex " << i << " is unreachable from the source." << std::endl;
        else 
            std::cout << distances[i] << std::endl;
    }
}

void Menu::runDemoAdjacencyMatrix()
{
    std::cout << "Running Dijkstra's Algorithm on Adjacency Matrix..." << std::endl;
    AdjacencyMatrixGraph graph(5);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 3, 9);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 4);
    graph.addEdge(4, 3, 6);

    auto distances = Dijkstra::findShortestPath(graph, 0);
    printDistances(distances);
}

void Menu::runDemoAdjacencyList()
{
    std::cout << "Running Dijkstra's Algorithm on Adjacency List..." << std::endl;
    AdjacencyListGraph graph(5);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 5);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 1, 3);
    graph.addEdge(2, 3, 9);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 4);
    graph.addEdge(4, 3, 6);

    auto distances = Dijkstra::findShortestPath(graph, 0);
    printDistances(distances);
}

void Menu::runExperiment()
{
    std::cout << "Running Experiment..." << std::endl;
    Driver driver;
    driver.run();
    std::cout << "Experiment completed. Results saved to results.csv" << std::endl;
}