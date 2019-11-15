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
