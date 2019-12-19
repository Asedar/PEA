#include "Algorithms.h"

void Algorithms::bruteForce(vector<int> &points, vector<int> &wayPoints, int currentPath, int parent)
{
    if(points.size() == 1)
    {
        currentPath += data->cityData[parent][points[0]];
        currentPath += data->cityData[points[0]][0];
        if(currentPath < data->minPath)
        {
            data->minPath = currentPath;
            data->path.clear();
            data->path = wayPoints;
            data->path.push_back(points[0]);
        }
        return;
    }
    for(int x = 0; x < points.size(); x++)
    {
        vector<int> newWayPoints = wayPoints;
        newWayPoints.push_back(points[x]);
        vector<int> newPoints = points;
        newPoints.erase(newPoints.begin() + x);
        bruteForce(newPoints, newWayPoints, currentPath + data->cityData[parent][points[x]], points[x]);
    }
}

int Algorithms::targetFunction(vector<vector<int>> &cityData)
{
    int value = 0;
    for(int x = 0; x < cityData.size(); x++)
    {
        if(x + 1 != cityData.size())
            value += cityData[x][x + 1];
        else
        {
            value += cityData[cityData.size() - 1][0];
        }
    }
    return value;
}

Algorithms::Algorithms(Data *data):data(data)
{

}

void Algorithms::branchAndBound()
{
    struct Node
    {
        vector<int> path;
        int point;
        int lowerBound;
        bool isLeaf = true;
        vector<vector<int>> modifiedCD;
        Node(vector<int> &path, int point, vector<vector<int>> modifiedCD)
        : path(path), point(point), modifiedCD(modifiedCD){}
    };
    data->clear();
    vector<Node*> nodeList;
    vector<int> path = {};
    nodeList.push_back(new Node( path, 0, data->cityData));
    nodeList[0]->lowerBound = reduceMatrix(nodeList[0]->modifiedCD);
    Node * currentNode = nodeList[0];
    currentNode->isLeaf = false;
    vector<int> cities = data->cities;

    while(true)
    {
        path.clear();
        path = currentNode->path;
        path.push_back(currentNode->point);
        if(path.size() == data->cities.size() + 1) break;
        cities = data->cities;
        for(int x = 0; x < currentNode->path.size(); x++)
        {
            cities.erase(std::remove(cities.begin(), cities.end(), currentNode->path[x]), cities.end());
        }
        cities.erase(std::remove(cities.begin(), cities.end(), currentNode->point), cities.end());
        for(int x = 0; x < cities.size(); x++)
        {
            nodeList.push_back(new Node(path, cities[x], currentNode->modifiedCD));
            nodeList.back()->lowerBound = reduceMatrix(nodeList.back()->modifiedCD, currentNode->point, cities[x]) + currentNode->lowerBound + currentNode->modifiedCD[currentNode->point][nodeList.back()->point];
        }
        int min = INT32_MAX;
        for(int x = 0; x < nodeList.size(); x++)
        {
            if(nodeList[x]->isLeaf && nodeList[x]->lowerBound < min)
            {
                currentNode = nodeList[x];
                min = currentNode->lowerBound;
            }
        }
        currentNode->isLeaf = false;

    }
    data->minPath = currentNode->lowerBound;
    data->path = path;
    for(int x = 0; x < nodeList.size(); x++)
    {
        delete nodeList[x];
    }

}

vector<int> Algorithms::dynamicProgramming(int point, vector<int> &cities)
{
    vector<int> path;
    vector<int> minPath;
    vector<int> val;
    minPath.push_back(INT32_MAX);
    int index = 0;
    string key = to_string(point);
    for(int x = 0; x < cities.size(); x++)
    {
        key += "," + to_string(cities[x]);
    }
    if(!cities.empty())
    {
        auto search = nodes.find(key);
        if(search != nodes.end())
        {
            string substr = "";
            for(int y = 0; y < search->second.length(); y++)
            {
                if(search->second[y] != ',')
                {
                    substr += search->second[y];
                }
                else
                {
                    val.push_back(stoi(substr));
                    substr = "";
                }
            }
            if(!substr.empty())
            {
                val.push_back(stoi(substr));
            }
            minPath = val;
        }
        else
        {
            for(int x = 0; x < cities.size(); x++)
            {
                vector<int> newCities = cities;
                newCities.erase(newCities.begin() + x);
                path = dynamicProgramming(cities[x], newCities);
                path[0] += data->cityData[point][cities[x]];
                if(path[0] < minPath[0])
                {
                    //cout<< endl << minPath[0] << " "<< path[0] << endl;
                    minPath = path;
                    index = x;
                }
            }
            //minPath[0] += data->cityData[point][cities[index]];
            //cout << endl << minPath[0] << " " << point << " " << cities[index]<<endl;
            minPath.push_back(cities[index]);
            string str = to_string(minPath[0]);
            for(int x = 1; x < minPath.size(); x++)
            {
               str += "," + to_string(minPath[x]);
            }
            nodes[key] = str;
        }
    }
    else
    {
        minPath[0] = data->cityData[point][0];
        //minPath.push_back(point);
    }
    return minPath;
}

void Algorithms::clearDataStructures()
{
    nodes.clear();
    //modifiedCD.clear();
}

int Algorithms::reduceMatrix(vector<vector<int>> &matrix, int xPoint, int yPoint)
{
    if(xPoint != -1 && yPoint != -1)
    {
        for(int x = 0; x < matrix.size(); x++)
        {
            matrix[xPoint][x] = -1;
            matrix[x][yPoint] = -1;
        }
        matrix[yPoint][xPoint] = -1;
    }
    int totalRow = 0, totalColumn = 0;
    for(int x = 0; x < matrix.size(); x++)
    {
        int min = INT32_MAX;
        for(int y = 0; y < matrix.size(); y++)
        {
            if(matrix[x][y] != -1 && matrix[x][y] < min)
            {
                min = matrix[x][y];
            }
        }

        if(min < INT32_MAX)
        {
            for(int y = 0; y < matrix.size(); y++)
            {
                if(matrix[x][y] != -1)
                {
                    matrix[x][y] -= min;
                }
            }
            totalRow += min;
        }
    }

    for(int x = 0; x < matrix.size(); x++)
    {
        int min = INT32_MAX;
        for(int y = 0; y < matrix.size(); y++)
        {
            if(matrix[y][x] != -1 && matrix[y][x] < min)
            {
                min = matrix[y][x];
            }
        }

        if(min < INT32_MAX)
        {
            for(int y = 0; y < matrix.size(); y++)
            {
                if(matrix[y][x] != -1)
                {
                    matrix[y][x] -= min;
                }
            }
            totalColumn += min;
        }
    }
    return totalColumn + totalRow;
}



void Algorithms::tabuSearch(long long time)
{
    struct Tabu
    {
        int pointX;
        int pointY;
        int time;
        Tabu(int pointX, int pointY, int time)
        : pointX(pointX), pointY(pointY), time(time)
        {

        }
    };
    bool end = false;
    vector<int> currentPath;
    generatePath(currentPath);
    vector<int> bestPath = currentPath;
    int bestMinPath = INT32_MAX;
    vector<Tabu*> tabu;
    int currentMinPath = INT32_MAX;
    auto start = chrono::steady_clock::now();
    int counter = 0;
    while(!end)
    {
        Tabu *newTabu = new Tabu(0,0,60);
        int neighbourPathLength = -1;
        vector<int> neighbourPath = currentPath;
        int min = INT32_MAX;

        for(int x = 1; x < currentPath.size() - 2; x++)
        {
            for(int y = x + 1; y < currentPath.size() -1; y++)
            {
                neighbourPath = currentPath;
                int temp = neighbourPath[x];
                neighbourPath[x] = neighbourPath[y];
                neighbourPath[y] = temp;
                neighbourPathLength = checkPathValue(neighbourPath);

                bool forbidden = false;
                for(int z = 0; z < tabu.size(); z++)
                {
                    if((tabu[z]->pointX == x && tabu[z]->pointY == y) || (tabu[z]->pointX == y && tabu[z]->pointY == x))
                    {
                        forbidden = true;
                        break;
                    }
                }
                if(forbidden && neighbourPathLength > bestMinPath)
                    continue;
                if(neighbourPathLength == -1)
                {
                    min = neighbourPathLength;
                    newTabu->pointX = x;
                    newTabu->pointY = y;
                }
                if(neighbourPathLength < min)
                {
                    min = neighbourPathLength;
                    newTabu->pointX = x;
                    newTabu->pointY = y;
                }
            }
        }
        currentMinPath = min;
        int temp = currentPath[newTabu->pointX];
        currentPath[newTabu->pointX] = currentPath[newTabu->pointY];
        currentPath[newTabu->pointY] = temp;
        if(currentMinPath < bestMinPath)
        {
            bestMinPath = currentMinPath;
            bestPath = currentPath;
            counter = 0;
        }
        else
            counter++;

        for(int i = 0; i < tabu.size(); i++)
        {
            tabu[i]->time--;
            if(tabu[i]->time == 0)
            {
                tabu.erase(tabu.begin() + i);
                i--;
                continue;
            }
        }
        tabu.push_back(newTabu);
        if(counter >= 100)
        {
            generateRandomPath(currentPath);
            currentMinPath = checkPathValue(currentPath);
            counter = 0;
        }
        auto checkpoint = chrono::steady_clock::now();
        //time--;
        //if(time == 0)
            //end = true;
        if(chrono::duration_cast<chrono::seconds>(checkpoint - start).count() >= time)
            end = true;
    }
    data->minPath = bestMinPath;
    data->path = bestPath;
}

void Algorithms::generatePath(vector<int> &path)
{
    path.clear();
    data->clear();
    path.push_back(0);
    int currentCity;
    int currentMinPath = 0;
    int index = 0;

    while(!data->cities.empty())
    {
        int currentValue = INT32_MAX;
        for(int x = 0; x < data->cities.size(); x++)
        {
            if(data->cityData[path.back()][data->cities[x]] < currentValue)
            {
                currentValue = data->cityData[path.back()][data->cities[x]];
                currentCity = data->cities[x];
                index = x;
            }
        }
        path.push_back(currentCity);
        currentMinPath += currentValue;
        data->cities.erase(data->cities.begin() + index);
    }
    data->minPath = currentMinPath + data->cityData[path.back()][0];
    path.push_back(0);
}

float Algorithms::checkPathValue(vector<int> &path)
{
    float value = 0;
    for(int x = 0; x < path.size() - 1; x++)
    {
        value += data->cityData[path[x]][path[x+1]];
    }
    return value;
}

void Algorithms::generateRandomPath(vector<int> &path)
{
    vector<int> tempPath;
    for(int x = 1; x < path.size() - 1; x++)
    {
        tempPath.push_back(path[x]);
    }
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(tempPath), std::end(tempPath), rng);
    path = tempPath;
    path.push_back(0);
    path.insert(path.begin(), 0);

}

void Algorithms::simulatedAnnealing(float temp, float coolingRate)
{
    vector<int> currentPath;
    generatePath(currentPath);
    float currentMinPath = checkPathValue(currentPath);

    vector<int> bestPath = currentPath;
    float bestMinPath = currentMinPath;
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    // initialize a uniform distribution between 0 and 1
    std::uniform_real_distribution<double> rand1(0, 1);


    while(temp > 1)
    {
        vector<int> neighbourPath = currentPath;
        int pointX = rand() %(currentPath.size() - 1) + 1;
        int pointY = rand() %(currentPath.size() - 1) + 1;
        while(true)
        {
            if(pointX == pointY)
            {
                pointY = rand() %(currentPath.size() - 1) + 1;
            }
            else
                break;
        }

        int help = neighbourPath[pointX];
        neighbourPath[pointX] = neighbourPath[pointY];
        neighbourPath[pointY] = help;
        float neighbourPathLength = checkPathValue(currentPath);
        if(neighbourPathLength < currentMinPath || ((neighbourPathLength - currentMinPath)/temp)<rand1(rng))
        {
            currentMinPath = neighbourPathLength;
            currentPath = neighbourPath;
        }
        if(currentMinPath < bestMinPath)
        {
            bestMinPath = currentMinPath;
            bestPath = currentPath;
        }
        temp *= 1-coolingRate;
    }
    data->path = bestPath;
    data->minPath = bestMinPath;
}
