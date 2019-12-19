//
// Created by milosz on 11/3/19.
//

#include "Data.h"

void Data::loadFile()
{
    fstream file;
    cout << "Podaj lokalizacje pliku: ";
    string localization;
    cin >> localization;
    file.open(localization);
    if(file.good())
    {
        int size;
        string title;
        file >> title;
        file >> size;
        cityData.clear();
        cityData.resize(size);
        cout << endl;
        for(int i = 0; i < size; i++)
        {
            for(int l = 0; l < size; l++)
            {
                int value;
                file >> value;
                cityData[i].push_back(value);
                cout << value << " ";
            }
            cout << endl;
        }
        cout << endl << "Plik " << title << " wczytany!" << endl;
        clear();
    }
    else
    {
        cout << endl << "Nie udalo sie wczytac pliku!" << endl;
    }
}

void Data::loadFile(string name)
{
    fstream file;

    file.open(name);
    if(file.good())
    {
        int size;
        string title;
        file >> title;
        file >> size;
        cityData.clear();
        cityData.resize(size);
        cout << endl;
        for(int i = 0; i < size; i++)
        {
            for(int l = 0; l < size; l++)
            {
                int value;
                file >> value;
                cityData[i].push_back(value);
                cout << value << " ";
            }
            cout << endl;
        }
        clear();
    }
}

void Data::generateData()
{
    cout << endl << "Podaj rozmiar: ";
    int size;
    cin >> size;
    cityData.clear();
    cityData.resize(size);
    cout << endl;
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            if(x == y)
            {
                cityData[x].push_back(-1);
            }
            else
            {
                cityData[x].push_back(rand() % (10 * size));
            }
            cout << cityData[x][y] << " ";
        }
        cout << endl;
    }
    cout << endl;
    clear();
}

void Data::clear()
{
    minPath = INT32_MAX;
    cities.clear();
    for(int x = 1; x < cityData.size(); x++)
    {
        cities.push_back(x);
    }
    path.clear();
}

void Data::randomMatrix(int size)
{
    cityData.clear();
    cityData.resize(size);
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < size; y++)
        {
            if(x == y)
            {
                cityData[x].push_back(-1);
            }
            else
            {
                cityData[x].push_back(rand() % (10 * size));
            }
        }
    }
    clear();
}
