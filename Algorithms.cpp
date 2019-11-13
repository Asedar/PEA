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

void Algorithms::clearNodes()
{
    nodes.clear();
}
