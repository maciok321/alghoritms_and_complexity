#include <iostream>
#include "Data.h"
#include "Sort.h"
#include <chrono>
#include <fstream>

enum class SortAlgorithm // enum do wyboru algorytmu sortowania w funkcji benchmarkowej
{
    QUICK_SORT,
    MERGE_SORT,
    INTRO_SORT
};

void runBenchmark(Data &movieData, int n, int iterations, SortAlgorithm algo, const std::string &algoName, std::ofstream &csvFile);

int main()
{
    std::cout << "\n=== TEST ZLOZONOSCI WCZYTYWANIA (O(N)) ===" << std::endl;

    int testLimits[] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};

    for (int i = 0; i < 11; i++)
    {
        int limit = testLimits[i];
        std::cout << "Test dla N = " << limit << "..." << std::endl;

        Data testLoadData(limit + 100);

        testLoadData.loadAndFilterData("data/csv/projekt1_dane.csv", limit); // wczytywanie danych z limitem, aby przetestować złożoność O(N)
    }
    std::cout << "==========================================\n";

    Data movieData(1100000);
    movieData.loadAndFilterData("data/csv/projekt1_dane.csv");

    const int s = 5;
    int n[s]{10000, 100000, 500000, 1000000, movieData.currentSize};
    int iterations = 1;
    Sort sort;

    std::ofstream csvFile("data/csv/benchmark_results.csv");
    csvFile << "Algorithm,N,AverageTime(ms),AverageRating,MedianRating\n";

    for (int i = 0; i < s; i++)
    {
        runBenchmark(movieData, n[i], iterations, SortAlgorithm::QUICK_SORT, "QuickSort", csvFile);
    }

    for (int i = 0; i < s; i++)
    {
        runBenchmark(movieData, n[i], iterations, SortAlgorithm::MERGE_SORT, "MergeSort", csvFile);
    }

    for (int i = 0; i < s; i++)
    {
        runBenchmark(movieData, n[i], iterations, SortAlgorithm::INTRO_SORT, "IntroSort", csvFile);
    }

    csvFile.close();
    std::cout << "Benchmark results saved to benchmark_results.csv" << std::endl;

    return 0;
}

void runBenchmark(Data &movieData, int n, int iterations, SortAlgorithm algo, const std::string &algoName, std::ofstream &csvFile)
{
    Sort sort;
    double totalTime = 0.0;
    double finalAverageRating = 0.0;
    double finalMedianRating = 0.0;
    int actualSize = 0;

    std::cout << "\n==========================================" << std::endl;
    std::cout << " Starting test for: " << algoName << " | N = " << n << std::endl;
    std::cout << "==========================================" << std::endl;

    for (int i = 0; i < iterations; i++) // wykonanie kilku iteracji dla każdego algorytmu i rozmiaru danych dla lepszego pomiaru czasu sortowania
    {
        Data *testData = movieData.getSubsetOfData(n);
        actualSize = testData->currentSize; // aktualny rozmiar danych mozliwe ze mniejszy od n, jeśli n przekracza dostępne dane

        auto start = std::chrono::high_resolution_clock::now();

        if (algo == SortAlgorithm::QUICK_SORT)
        {
            sort.quickSort(testData->data, 0, testData->currentSize - 1);
        }
        else if (algo == SortAlgorithm::MERGE_SORT)
        {
            sort.mergeSort(testData->data, 0, testData->currentSize - 1);
        }
        else if (algo == SortAlgorithm::INTRO_SORT)
        {
            sort.introSort(testData->data, testData->currentSize);
        }

        auto end = std::chrono::high_resolution_clock::now();
        totalTime += std::chrono::duration<double, std::milli>(end - start).count(); // pomiar czasu sortowania w milisekundach
        if (sort.isSorted(testData->data, testData->currentSize))                    // weryfikacja poprawności posortowania danych po każdej iteracji
        {
            std::cout << " -> Iteracja " << i + 1 << ": OK.\n";
        }
        else
        {
            std::cerr << " -> Iteracja " << i + 1 << ": NIE!!!\n";
            std::exit(1);
        }

        if (i == iterations - 1) // obliczenie średniej i mediany ocen filmów tylko dla ostatniej iteracji
        {
            double sumRating = 0;
            for (int j = 0; j < testData->currentSize; j++)
            {
                sumRating += testData->data[j].rating;
            }
            double averageRating = sumRating / testData->currentSize;
            finalAverageRating = averageRating;

            double medianRating = 0;
            int mid = testData->currentSize / 2;
            if (testData->currentSize % 2 == 0)
            {
                medianRating = (testData->data[mid - 1].rating + testData->data[mid].rating) / 2.0;
            }
            else
            {
                medianRating = testData->data[mid].rating;
            }
            finalMedianRating = medianRating;

            std::cout << " -> Srednia ocena filmow: " << averageRating << std::endl;
            std::cout << " -> Mediana ocen filmow: " << medianRating << std::endl;
        }

        delete testData;
    }

    std::cout << " -> Sredni czas sortowania (" << iterations << " prob): "
              << totalTime / iterations << " ms\n"
              << std::endl;

    csvFile << algoName << ","
            << actualSize << ","
            << totalTime / iterations << ","
            << finalAverageRating << ","
            << finalMedianRating << "\n";
}