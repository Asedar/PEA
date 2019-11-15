#ifndef PEA_ALGORITHMS_H
#define PEA_ALGORITHMS_H

#include <vector>
#include <unordered_map>
#include "Data.h"
#include <algorithm>

using namespace std;


class Algorithms
{
public:

    Algorithms(Data *data);
    void bruteForce(vector<int> &points, vector<int> &wayPoints , int currentPath, int parent);
    int targetFunction(vector<vector<int>> &cityData);
    void branchAndBound();
    vector<int> dynamicProgramming(int point, vector<int> &cities);
    void clearDataStructures();
private:
    Data *data;
    unordered_map<string, string> nodes;

    //vector<vector<int>> modifiedCD;

    int reduceMatrix(vector<vector<int>> &matrix, int xPoint = -1, int yPoint = -1);
};

#endif //PEA_ALGORITHMS_H
