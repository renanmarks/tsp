#include <iostream>
#include <fstream>
#include "tsplibdata.h"
#include "tspcanonicaltest.h"
#include "tspgreedyconstruct.h"

void test(std::string filename)
{
    tsp::TSPLibData data;
    std::ifstream file(filename);
    data.load(file);

    tsp::TSPCanonicalTest test(data);
    tsp::TSPTour tour = test.run();

    tour.print(std::cout);
}

void testRun()
{
    std::cout << "pcb442.tsp" << std::endl;
    test("pcb442.tsp");

    std::cout << "gr666.tsp" << std::endl;
    test("gr666.tsp");

    std::cout << "att532.tsp" << std::endl;
    test("att532.tsp");
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "Inform filename." << std::endl;
        return 1;
    }

    std::string option = argv[1];

    if (option == "--test")
    {
        testRun();
        return 0;
    }

    tsp::TSPLibData data;
    std::ifstream file(option);
    data.load(file);

    tsp::TSPGreedyConstruct greedy(data);

    greedy.run().print(std::cout);

    return 0;
}
