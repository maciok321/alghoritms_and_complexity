#ifndef DATA_H
#define DATA_H
#include <string>

#pragma once

struct Movie
{
    std::string movie_name;
    float rating;
};

class Data
{
public:
    Movie *data;
    int currentSize;
    int capacity;

    Data(int maxSize);
    ~Data();

    void addMovie(const std::string &name, float rating);
    void loadAndFilterData(const std::string &filename, int limit = -1);
    Data *getSubsetOfData(int subsetSize);
};

#endif