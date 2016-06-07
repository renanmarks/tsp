#include <iostream>
#include <fstream>
#include "tsplibdata.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "Inform filename." << std::endl;

        return 1;
    }

    std::string filename = argv[1];

    tsp::TSPLibData data;
    std::ifstream file(filename);

    data.load(file);

    return 0;
}
