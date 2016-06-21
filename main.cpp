#include <iostream>
#include <fstream>
#include "tsplibdata.h"
#include "tspcanonicaltest.h"
#include "tspgrasp.h"
#include "tspnearestneighborconstruct.h"
#include "tsp2opt.h"
#include "tsptabu.h"

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

void printHelp(std::string executableName)
{
    std::cout << "Usage:\n"
              << "\t" << executableName << " [option] filename\n"
              << "Options:\n"
              << "\t--help              : Prints this help message.\n"
              << "\t--test              : Runs the Canonnical Tests from TSPLIB.\n"
              << "\t--only-constructive : Runs only the Nearest Neighbour construtive greedy heuristic.\n"
              << "\t--localsearch       : Runs the Nearest Neighbour with 2-Opt local search.\n"
              << "\t--grasp             : Runs the Nearest Neighbour with 2-Opt using GRASP metaheuristic.\n"
              << "\t--tabu              : Runs the Nearest Neighbour with 2-Opt using Tabu Search metaheuristic.\n"
              << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "Error: Please inform options and filename." << std::endl;
        printHelp(argv[0]);
        return 1;
    }

    std::string option = argv[1];

    if (option == "--test")
    {
        testRun();
        return 0;
    }

    if (option == "--help")
    {
        printHelp(argv[0]);
        return 0;
    }

    tsp::TSPLibData data;
    std::ifstream file(argv[2]);

    if (!file.is_open())
    {
        std::cout << "Error: cannot open file." << std::endl;
        printHelp(argv[0]);
        return 0;
    }

    data.load(file);

    if (option == "--only-constructive")
    {
        tsp::TSPNearestNeighborConstruct nn(data);
        tsp::TSPTour tour = nn.run();

        if (tour.isValid())
        {
            tour.print(std::cout);
        }
        return 0;
    }

    if (option == "--localsearch")
    {
        tsp::TSPNearestNeighborConstruct nn(data);
        tsp::TSPTour tour = nn.run();

        tsp::TSP2opt local(data, tour);
        tour = local.run();

        if (tour.isValid())
        {
            tour.print(std::cout);
        }
        return 0;
    }

    if (option == "--grasp")
    {
        tsp::TSPGrasp grasp(data, 100);
        tsp::TSPTour tourGrasp = grasp.run();

        if ( tourGrasp.isValid() )
        {
            tourGrasp.print(std::cout);
        }
        return 0;
    }

    if (option == "--tabu")
    {
        tsp::TSPTabu tabu(data, 100, 10, 10);
        tsp::TSPTour tourTabu = tabu.run();

        if ( tourTabu.isValid() )
        {
            tourTabu.print(std::cout);
        }
        return 0;
    }

    return 0;
}
