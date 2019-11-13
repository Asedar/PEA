#ifndef PEA_ALGORITHMS_H
#define PEA_ALGORITHMS_H

#include <vector>
#include <unordered_map>
#include "Data.h"

using namespace std;


class Algorithms
{
public:

    Algorithms(Data *data);
    void bruteForce(vector<int> &points, vector<int> &wayPoints , int currentPath, int parent);
    int targetFunction(vector<vector<int>> &cityData);
    void branchAndBound();
    vector<int> dynamicProgramming(int point, vector<int> &cities);
    void clearNodes();
private:
    Data *data;
    unordered_map<string, string> nodes;
};

#endif //PEA_ALGORITHMS_H
