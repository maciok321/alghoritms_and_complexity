#ifndef SORT_H
#define SORT_H
#include "Data.h"

class Sort
{
public:
    void quickSort(Movie *array, int low, int high);
    void mergeSort(Movie *array, int left, int right);
    void introSort(Movie *array, int size);
    void printArray(Movie *array, int size);
    bool isSorted(Movie *array, int size);

private:
    void merge(Movie *array, Movie *temp, int left, int mid, int right); // funkcja pomocnicza dla algorytmu MergeSort, która scala dwie posortowane części tablicy
    void mergeSortUtil(Movie *array, Movie *temp, int left, int right);  // funkcja pomocnicza dla algorytmu MergeSort, która implementuje rekurencyjne dzielenie i scalanie tablicy
    void introSortUtil(Movie *array, int low, int high, int depthLimit); // funkcja pomocnicza dla algorytmu IntroSort, która decyduje, kiedy przejść z QuickSort na HeapSort lub InsertionSort
    int partition(Movie *array, int low, int high);                      // funkcja dzieląca dla algorytmu QuickSort
    void heapSort(Movie *array, int size);                               // funkcja pomocnicza dla algorytmu IntroSort, która implementuje sortowanie przez kopcowanie (HeapSort) dla części tablicy, gdy limit głębokości zostanie przekroczony
    void heapify(Movie *array, int size, int parent);                    // funkcja pomocnicza do utrzymania własności kopca dla algorytmu HeapSort
    void insertionSort(Movie *array, int left, int right);               // funkcja pomocnicza dla algorytmu IntroSort, która implementuje sortowanie przez wstawianie (InsertionSort) dla małych podtablic
};

#endif
