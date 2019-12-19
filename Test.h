#ifndef PEA_TEST_H
#define PEA_TEST_H


#include "Data.h"
#include "Algorithms.h"
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;

class Test
{
public:
    Test(Data *data, Algorithms *alg);
    void randomDataAutoTest(void (*testFunction)(), int size, int howManyTries);
    void fixedDataTest(int howManyTries);

private:
    Data *data;
    Algorithms *alg;
    vector<long long> times;
    void saveTimes(string fileName);
};


#endif //PEA_TEST_H
