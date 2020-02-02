//
// Created by milosz on 11/4/19.
//

#include "Test.h"

void Test::randomDataAutoTest(void (*testFunction)(), int size, int howManyTries)
{
    data->randomMatrix(size);
    for(int x = 0; x < howManyTries; x++)
    {
        auto start = chrono::high_resolution_clock::now();
        (*testFunction)();
        auto end = chrono::high_resolution_clock::now();
        times.push_back(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
    }
    string fileName = "C:\\Users\\Milosz\\Desktop\\PEA\\tests" + to_string(size) + " " + to_string(howManyTries) + ".txt";
    saveTimes(fileName);
}

Test::Test(Data *data, Algorithms *alg): data(data), alg(alg)
{

}

void Test::saveTimes(string fileName)
{
    ofstream file(fileName);

    for(int x = 0; x < times.size(); x++)
    {
        file << times[x] << "\n";
    }
    file.close();
}

void Test::fixedDataTest(int howManyTries)
{
    string path = "C:\\Users\\Milosz\\Desktop\\PEA\\SMALL\\data";
    string name;
    for(int y = 10; y < 19; y++)
    {
        name = to_string(y) + ".txt";
        data->loadFile(path + name);
        for(int x = 0; x < 1; x++)
        {
            alg->clearDataStructures();
            data->clear();
            auto start = chrono::steady_clock::now();
            alg->bruteForce(data->cities, data->path, 0, 0);
            auto end = chrono::steady_clock::now();
            times.push_back(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
        }
        string fileName = "C:\\Users\\Milosz\\Desktop\\PEA\\tests\\" + to_string(y) + ".txt";
        saveTimes(fileName);
        times.clear();
    }


}

void Test::fixedDataTest()
{
    string path = "C:\\Users\\Milosz\\Desktop\\PEA\\ATSP\\ATSP\\data";
    string name;
    alg->clearDataStructures();
    data->clear();
    data->loadFile(path + "34.txt");

    for(int y = 10; y < 19; y++)
    {
        name = to_string(y) + ".txt";
        data->loadFile(path + name);
        for(int x = 0; x < 1; x++)
        {
            alg->clearDataStructures();
            data->clear();
            auto start = chrono::steady_clock::now();
            alg->bruteForce(data->cities, data->path, 0, 0);
            auto end = chrono::steady_clock::now();
            times.push_back(chrono::duration_cast<chrono::nanoseconds>(end - start).count());
        }
        string fileName = "C:\\Users\\Milosz\\Desktop\\PEA\\tests\\" + to_string(y) + ".txt";
        saveTimes(fileName);
        times.clear();
    }


}

