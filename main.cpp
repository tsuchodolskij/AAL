#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

int readFromFile(char* filename, std::vector<int>& vec, int &n)
{
    std::ifstream inputFile;
    inputFile.open(filename, std::ios::in);

    if(!inputFile.is_open())
    {
        std::cout << filename << " can not be opened\n";
        return 0;
    }

    int value;
    while (inputFile >> value)
    {
        vec.push_back(value);
    }

    std::cout << filename << " has been read successfully\n";

    n = vec.size();
    std::cout << "Read " << vec.size() << " numbers" << std::endl;
    inputFile.close();
    return 1;
}

void launchGenerator(std::vector<int>& vec, const int n)
{
    std::cout << "Generator launched\n";
    srand (time(NULL));
    for (int i = 0; i < n; i++)
        vec.push_back(rand() % 10 + 1);

        for (unsigned i = 0; i < vec.size(); i++) std::cout << vec[i] <<  " ";
    std::cout << std::endl;
}

int sumVector (std::vector<int>& vec)
{
    return std::accumulate(vec.begin(), vec.end(), 0);
}

int main(int argc, char** argv)
{

    int n; // number of arguments
    std::vector<int> distances; // vector for input to be stored

    if(argv[1][0] == '-' && argv[1][1] == 'h')
    {
        std::cout << "Generator: ./exe [number of vertices]" << std::endl << "Reading from file: ./exe [file name]";
        return 0;
    }

    if (argc == 2)
    {
        if (atoi(argv[1]))
        {
            n = atoi(argv[1]);
            launchGenerator(distances, n);
            std::cout << n << " numbers successfully generated\n";
        }
        else if (readFromFile(argv[1], distances, n) == 1)
            std::cout << argv[1] << " has been closed successfully\n";
        else return 0;
    }
    else
    {
        std::cout << "Invalid arguments.\nUse -h for help.";
        return 0;
    }

    int totalDistance = sumVector(distances);
    int length = 0;
    int verticeHead = 0;
    int furtherDistance, closerDistance;
    int pairedVertice[n] = {};
    int res[n] = {};

    bool flag = false;

    for(int i = 0; i < n; i++)
    {
        std::cout << "--------------iteration-------------\n"; //-------------------------------------------------------------------
        while (length < (int) totalDistance/2)
        {
            length += distances[verticeHead];
            ++verticeHead;
            verticeHead %= n;
        }
        std::cout << "length: " << length << std::endl; //-------------------------------------------------------------------
        std::cout << "verticeHead: " << verticeHead << std::endl; //-------------------------------------------------------------------
        if ((length == (int)(totalDistance/2)) || ((length == (int)(totalDistance/2) + 1) && (totalDistance % 2 == 1)))
        {
            std::cout << "Wierzcholki " << i << " i " << verticeHead << ". Dlugosc: " << (int) totalDistance/2;
            flag = true;
            break;
        }
        furtherDistance = totalDistance - length;
        closerDistance = (verticeHead != 0) ? length - distances[verticeHead-1] : length - distances[n-1];

        std::cout << "furtherDistance: " << furtherDistance << std::endl; //-------------------------------------------------------------------
        std::cout << "closerDistance: " << closerDistance << std::endl; //-------------------------------------------------------------------

        res[i] = std::max(furtherDistance, closerDistance);
        std::cout << "res[i]: " << res[i] << std::endl; //-------------------------------------------------------------------
        std::cout << "verticeHead: " << verticeHead << std::endl; //-------------------------------------------------------------------
        pairedVertice[i] = res[i] == furtherDistance ? verticeHead - 1 : verticeHead;
        std::cout << "pairedVertice[i]: " << pairedVertice[i] << std::endl; //-------------------------------------------------------------------
        length -= distances[i];
        std::cout << "length: " << length << std::endl; //-------------------------------------------------------------------
    }

    if(flag) return 0;

    for (unsigned i = 0; i < distances.size(); i++) std::cout << distances[i] <<  " ";
    std::cout << std::endl;

    std::cout << "Paired vertices + Distance\n";
    for (int i = 0; i < n; i++) {
        std::cout << i << " " << pairedVertice[i] << ". Distance: " << res[i] << std::endl;
    }


    return 0;
}
