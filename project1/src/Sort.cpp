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

int Sort::partition(Movie *array, int low, int high)
{
    float pivot = array[(low + high) / 2].rating;
    int i = low;
    int j = high;
    while (true)
    {
        while (array[i].rating < pivot)
        {
            i++;
        }

        while (array[j].rating > pivot)
        {
            j--;
        }

        if (i >= j)
        {
            return j;
        }

        Movie temp = array[i];
        array[i] = array[j];
        array[j] = temp;

        i++;
        j--;
    }
}

void Sort::quickSort(Movie *array, int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);
        quickSort(array, low, pi);
        quickSort(array, pi + 1, high);
    }
}

void Sort::heapify(Movie *array, int size, int parent)
{
    int largest = parent;
    int left = 2 * parent + 1;
    int right = 2 * parent + 2;

    if (left < size && array[left].rating > array[largest].rating)
    {
        largest = left;
    }
    if (right < size && array[right].rating > array[largest].rating)
    {
        largest = right;
    }
    if (largest != parent)
    {
        Movie temp = array[parent];
        array[parent] = array[largest];
        array[largest] = temp;
        heapify(array, size, largest);
    }
}

void Sort::heapSort(Movie *array, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(array, size, i);
    }
    for (int i = size - 1; i > 0; i--)
    {
        Movie temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        heapify(array, i, 0);
    }
}

void Sort::introSortUtil(Movie *array, int low, int high, int depthLimit)
{
    if (low < high)
    {
        if (depthLimit == 0)
        {
            heapSort(array + low, high - low + 1);
            return;
        }

        int pi = partition(array, low, high);
        introSortUtil(array, low, pi, depthLimit - 1);
        introSortUtil(array, pi + 1, high, depthLimit - 1);
    }
}

void Sort::introSort(Movie *array, int size)
{
    int depthLimit = 2 * log2(size);
    introSortUtil(array, 0, size - 1, depthLimit);
}

void Sort::mergeSort(Movie *array, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }
}

void Sort::merge(Movie *array, int left, int mid, int right)
{
    Movie *temp = new Movie[right - left + 1];
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

    delete[] temp;
}
