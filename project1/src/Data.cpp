#include "Data.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Data::Data(int maxSize)
{
    data = new Movie[maxSize];
    currentSize = 0;
    capacity = maxSize;
}

Data::~Data() { delete[] data; }

void Data::addMovie(const std::string &name, float rating)
{
    if (currentSize < capacity)
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

void Data::loadAndFilterData(const std::string &filename, int limit)
{
    std::ifstream file(filename); // otwarcie pliku CSV
    if (!file.is_open())
    {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // pomijanie nagłówka CSV
    auto start = std::chrono::high_resolution_clock::now();

    while (std::getline(file, line)) // czytanie każdej linii z pliku
    {
        if (limit != -1 &&
            currentSize >=
                limit) // sprawdzenie limitu, jeśli został ustawiony (potrzebne do
                       // testow zlozonosci wczytywania danych)
        {
            break;
        }

        size_t lastComma =
            line.find_last_of(','); // znalezienie ostatniego przecinka, który
                                    // oddziela nazwę filmu od oceny
        size_t firstComma = line.find_first_of(
            ','); // znalezienie pierwszego przecinka, który oddziela ID od nazwy
                  // filmu (w przypadku gdy nazwa filmu zawiera przecinek)
        if (lastComma != std::string::npos && firstComma != std::string::npos &&
            lastComma != firstComma)
        {
            std::string name = line.substr(
                firstComma + 1, lastComma - firstComma -
                                    1); // wyodrębnienie nazwy filmu, uwzględniając
                                        // możliwość występowania przecinków w nazwie
            std::string ratingString =
                line.substr(lastComma + 1); // wyodrębnienie oceny filmu jako string

            if (!ratingString.empty())
            {
                try
                {
                    float ratingValue =
                        std::stof(ratingString); // konwersja ze string na float
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
    std::cout << "Data loading and filtering took: " << duration.count()
              << " seconds." << std::endl;
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