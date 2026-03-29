#ifndef SORT_H
#define SORT_H
#include "Data.h"

#pragma once

class Sort
{
public:
    void quickSort(Movie *array, int low, int high);
    void mergeSort(Movie *array, int left, int right);
    void introSort(Movie *array, int size);
    void printArray(Movie *array, int size);

private:
    void merge(Movie *array, int left, int mid, int right);
    void introSortUtil(Movie *array, int low, int high, int depthLimit);
    int partition(Movie *array, int low, int high);
    void heapSort(Movie *array, int size);
    void heapify(Movie *array, int size, int parent);
};

#endif