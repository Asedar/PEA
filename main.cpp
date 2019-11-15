#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "Algorithms.h"
#include "Data.h"
#include "Test.h"

using namespace std;

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
}

void showMenu()
{
    cout << "Dostepne opcje: " << endl
        << "1. Wczytaj dane z pliku" << endl
        << "2. Generuj losowe dane" << endl
        << "3. Brute force" << endl
        << "4. Branch & bound" << endl
        << "5. Programowanie dynamiczne" << endl
        << "6. Wartosc funkcji celu" << endl
        << "7. Zakoncz" << endl;
}

void firstStageMenu()
{
    cout << "Wybierz algorytm: " << endl
    << "1. Brute force" << endl
    << "2. Branch & bound" << endl
    << "3. Programowanie dynamiczne" << endl
    << "4. Powrot" << endl;
}

//void secondStageMenu();
//void thirdStageMenu();

int main()
{
    srand( time( NULL ) );
    Data *data = new Data();
    Algorithms algorithms(data);
    Test test(data);

    while(1)
    {
        if(data->cityData.empty())
        {
            cout << "Nie wczytano zadnych danych" << endl << endl;
        }
        showMenu();
        int choice;
        cin >> choice;
        switch(choice)
        {
            case 1:
                clearScreen();
                data->loadFile();
                break;
            case 2:
                clearScreen();
                data->generateData();
                break;
            case 3:
            {
                if(data->cityData.empty())
                {
                    break;
                }
                data->clear();
                algorithms.bruteForce(data->cities, data->path, 0, 0);
                cout << endl << data->minPath << " " << endl << "0 ";
                for(int x = data->path.size() - data->cityData.size() + 1; x < data->path.size(); x++)
                {
                    cout << data->path[x] << " ";
                }
                cout << endl;
                break;
            }
            case 4:
                if(data->cityData.empty())
                {
                    break;
                }
                algorithms.branchAndBound();
                cout << endl << data->minPath << " " << endl << "0 ";
                for(int x = data->path.size() - data->cityData.size() + 1; x < data->path.size(); x++)
                {
                    cout << data->path[x] << " ";
                }
                cout << endl;
                break;
            case 5:
            {
                if(data->cityData.empty())
                {
                    break;
                }

                algorithms.clearDataStructures();
                data->clear();
                vector<int> path = algorithms.dynamicProgramming(0, data->cities);
                cout << endl << "0 ";
                for(int x = path.size() - 1; x > 0; x--)
                {
                    cout << path[x] << " ";
                }
                cout << endl << path[0] << endl;
                break;
            }
            case 6:
                if(data->cityData.empty())
                {
                    break;
                }
                cout << endl << algorithms.targetFunction(data->cityData) << endl;
                break;
            case 7:
                return 0;
            default:
                cout << "Wybrana opcja jest nieprawidlowa!" << endl;
                break;
        }
    }
    return 0;
}