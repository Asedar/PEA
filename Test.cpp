//
// Created by milosz on 11/4/19.
//

#include "Test.h"

void Test::randomDataAutoTest(void (*testFunction)(), int size, int howManyTries)
{
    data->randomMatrix(size);
    for(int x = 0; x < howManyTries; x++)
    {
        auto start = chrono::steady_clock::now();
        (*testFunction)();
        auto end = chrono::steady_clock::now();
        times.push_back(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
    }
    string fileName = "./tests/" + to_string(size) + " " + to_string(howManyTries) + ".txt";
    saveTimes(fileName);
}

Test::Test(Data *data): data(data)
{

}

void Test::saveTimes(string fileName)
{
    float average = 0;
    for(int x = 0; x < times.size(); x++)
    {
        average += times[x];
    }
    average /= times.size();
    ofstream file(fileName);
    for(int x = 0; x < data->cityData.size(); x++)
    {
        for(int y = 0; y < data->cityData[x].size(); y++)
        {
            file << data->cityData[x][y] << " ";
        }
        file << "\n";
    }
    file << average << "\n";
    for(int x = 0; x < times.size(); x++)
    {
        file << times[x] << "\n";
    }
    file.close();
}
