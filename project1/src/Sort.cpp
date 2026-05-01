#include "Sort.h"
#include "Data.h"
#include <cmath>
#include <iostream>

void Sort::printArray(Movie *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i].movie_name << " - " << array[i].rating << std::endl;
    }
}

bool Sort::isSorted(Movie *array, int size)
{
    if (size <= 1)
    {
        return true;
    }

    for (int i = 1; i < size; i++)
    {
        if (array[i - 1].rating > array[i].rating)
        {
            return false;
        }
    }

    return true;
}

int Sort::partition(Movie *array, int low, int high)
{
    float pivot = array[(low + high) / 2].rating; // wybór środkowego elementu jako pivot (schemat Hoare'a)
    int i = low;
    int j = high;
    while (true)
    {
        while (array[i].rating < pivot) // iteracja od lewej strony
        {
            i++;
        }

        while (array[j].rating > pivot) // iteracja od prawej strony
        {
            j--;
        }

        if (i >= j) // jeśli wskaźniki się spotkają lub miną zwraca indeks j jako punkt podziału
        {
            return j;
        }

        std::swap(array[i], array[j]); // zamiana elementów, jeśli są po niewłaściwej stronie pivotu

        i++;
        j--;
    }
}

void Sort::quickSort(Movie *array, int low, int high)
{
    if (low < high) // warunek rekurencji, sortowanie odbywa się tylko wtedy, gdy jest więcej niż jeden element
    {
        int pi = partition(array, low, high);
        quickSort(array, low, pi);      // rekurencyjne sortowanie lewej części
        quickSort(array, pi + 1, high); // rekurencyjne sortowanie prawej części
    }
}

void Sort::heapify(Movie *array, int size, int parent)
{
    int largest = parent;
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if (left < size && array[left].rating > array[largest].rating) // porównanie z lewym dzieckiem
    {
        largest = left;
    }
    if (right < size && array[right].rating > array[largest].rating) // porównanie z prawym dzieckiem
    {
        largest = right;
    }
    if (largest != parent)
    {
        std::swap(array[parent], array[largest]); // zamiana elementu rodzica z największym elementem
        heapify(array, size, largest);            // rekurencyjne heapify dla poddrzewa, które zostało zmienione
    }
}

void Sort::heapSort(Movie *array, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i); // budowanie kopca (max-heap) od ostatniego nie-liścia do korzenia
    }
    for (int i = size - 1; i > 0; i--) // sortowanie poprzez usuwanie elementu z kopca i umieszczanie go na końcu tablicy
    {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

void Sort::insertionSort(Movie *array, int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        Movie key = array[i];
        int j = i - 1;
        while (j >= left && array[j].rating > key.rating)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void Sort::introSortUtil(Movie *array, int low, int high, int depthLimit)
{
    int size = high - low + 1;
    if (size < 16) // dla małych podtablic sortowanie przez wstawianie
    {
        insertionSort(array, low, high);
        return;
    }

    if (depthLimit == 0) // gdy limit głębokości osiągnięty zmiana na heap sort
    {
        heapSort(array + low, high - low + 1);
        return;
    }

    int pi = partition(array, low, high);               // podział tablicy i rekurencyjne sortowanie obu części
    introSortUtil(array, low, pi, depthLimit - 1);      // sortowanie lewej części
    introSortUtil(array, pi + 1, high, depthLimit - 1); // sortowanie prawej części
}

void Sort::introSort(Movie *array, int size)
{
    int depthLimit = 2 * log2(size); // obliczenie limitu głębokości jako 2 * log2(n)
    introSortUtil(array, 0, size - 1, depthLimit);
}

void Sort::mergeSort(Movie *array, int left, int right)
{
    Movie *temp = new Movie[right - left + 1]; // tymczasowa tablica do scalania implementowana jednorazowo, aby uniknąć wielokrotnego alokowania pamięci podczas rekurencji
    mergeSortUtil(array, temp, left, right);
    delete[] temp;
}

void Sort::mergeSortUtil(Movie *array, Movie *temp, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortUtil(array, temp, left, mid);
        mergeSortUtil(array, temp, mid + 1, right);
        merge(array, temp, left, mid, right);
    }
}

void Sort::merge(Movie *array, Movie *temp, int left, int mid, int right)
{
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right)
    {
        if (array[i].rating < array[j].rating)
        {
            temp[k] = array[i];
            k++;
            i++;
        }
        else
        {
            temp[k] = array[j];
            k++;
            j++;
        }
    }

    while (i <= mid)
    {
        temp[k] = array[i];
        k++;
        i++;
    }

    while (j <= right)
    {
        temp[k] = array[j];
        k++;
        j++;
    }

    for (int i = 0; i < k; i++)
    {
        array[left + i] = temp[i];
    }
}
