#ifndef PEA_TEST_H
#define PEA_TEST_H


#include "Data.h"
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;

class Test
{
public:
    Test(Data *data);
    void randomDataAutoTest(void (*testFunction)(), int size, int howManyTries);

private:
    Data *data;
    vector<int> times;
    void saveTimes(string fileName);
};


#endif //PEA_TEST_H
