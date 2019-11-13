#ifndef PEA_DATA_H
#define PEA_DATA_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Data
{
public:
    vector<vector<int>> cityData;
    int minPath = INT32_MAX;
    vector<int> cities;
    vector<int> path;

    void loadFile();
    void generateData();
    void clear();
    void randomMatrix(int size);
};


#endif //PEA_DATA_H
