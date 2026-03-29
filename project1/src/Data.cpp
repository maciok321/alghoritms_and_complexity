#include "Data.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <chrono>

Data::Data(int maxSize)
{
    data = new Movie[maxSize];
    currentSize = 0;
    capacity = maxSize;
}

Data::~Data()
{
    delete[] data;
}

void Data::addMovie(const std::string &name, float rating)
{
    if (currentSize <= capacity)
    {
        data[currentSize].movie_name = name;
        data[currentSize].rating = rating;
        currentSize++;
    }
    else
    {
        std::cerr << "Data capacity exceeded!" << std::endl;
    }
}

void Data::loadAndFilterData(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header line
    auto start = std::chrono::high_resolution_clock::now();

    while (std::getline(file, line))
    {
        size_t lastComma = line.find_last_of(',');
        if (lastComma != std::string::npos)
        {
            std::string name = line.substr(0, lastComma);
            std::string ratingString = line.substr(lastComma + 1);

            if (!ratingString.empty())
            {
                try
                {
                    float ratingValue = std::stof(ratingString);
                    addMovie(name, ratingValue);
                }
                catch (...)
                {
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Data loading and filtering took: " << duration.count() << " seconds." << std::endl;
    std::cout << "Loaded " << currentSize << " movies." << std::endl;

    file.close();
}

Data *Data::getSubsetOfData(int subsetSize)
{
    if (subsetSize > currentSize)
    {
        subsetSize = currentSize;
    }

    Data *subset = new Data(subsetSize);
    for (int i = 0; i < subsetSize; i++)
    {
        subset->addMovie(data[i].movie_name, data[i].rating);
    }

    return subset;
}