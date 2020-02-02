#ifndef PEA_ALGORITHMS_H
#define PEA_ALGORITHMS_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Data.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <math.h>

using namespace std;


class Algorithms
{
public:

    Algorithms(Data *data);
    void bruteForce(vector<int> &points, vector<int> &wayPoints , int currentPath, int parent);
    int targetFunction(vector<vector<int>> &cityData);
    void branchAndBound();
    void tabuSearch(long long time);
    void simulatedAnnealing(float temp, float coolingRate);
    vector<int> dynamicProgramming(int point, vector<int> &cities);
    void geneticAlgorithm(int initialPopulation, float mutationChance, int generations, float crossingChance, int crossType);
    void clearDataStructures();
private:
    Data *data;
    unordered_map<string, string> nodes;

    //vector<vector<int>> modifiedCD;
    struct Fitness
    {
        vector<int>path;
        float pathValue;
        float fitness;
        Fitness(vector<int>path, float pathV):path(path), pathValue(pathV)
        {
            fitness = 1.0f/pathV;
        }
    };

    int reduceMatrix(vector<vector<int>> &matrix, int xPoint = -1, int yPoint = -1);
    void generatePath(vector<int> &path);
    void generateRandomPath(vector<int> &path);
    float checkPathValue(vector<int> &path);
    void bestDraft(int &A, int &B, vector<Fitness> pop);
    void rouletteDraft(int &A, int &B, vector<Fitness> pop);
    void OXCrossing(vector<int> &path, Fitness parentA, Fitness parentB);


};

#endif //PEA_ALGORITHMS_H
