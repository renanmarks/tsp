#include <iostream>
#include <fstream>
#include "tsplibdata.h"
#include "tspcanonicaltest.h"

void test(std::string filename)
{
    tsp::TSPLibData data;
    std::ifstream file(filename);
    data.load(file);

    tsp::TSPCanonicalTest test(data);
    tsp::TSPTour tour = test.run();

    tour.print(std::cout);
}

int main(int argc, char *argv[])
{
//    if (argc <= 1)
//    {
//        std::cout << "Inform filename." << std::endl;

//        return 1;
//    }

//    std::string filename = argv[1];

//    tsp::TSPLibData data;
//    std::ifstream file(filename);
//    data.load(file);

    std::cout << "pcb442.tsp" << std::endl;
    test("pcb442.tsp");

    std::cout << "gr666.tsp" << std::endl;
    test("gr666.tsp");

    std::cout << "att532.tsp" << std::endl;
    test("att532.tsp");

    return 0;
}
