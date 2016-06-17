#include "tsp2opt.h"
#include "tspgrasp.h"
#include "tspnearestneighborconstruct.h"

tsp::TSPGrasp::TSPGrasp(const tsp::TSPLibData &_data, uint32_t _numberIterations)
    : data(_data), numberIterations(_numberIterations)
{

}

tsp::TSPTour tsp::TSPGrasp::run()
{
    // TODO: Build better architecture :)
    tsp::TSPNearestNeighborConstruct nearestNeighbor(this->data);
    tsp::TSPTour bestTour(this->data);

    std::uint32_t maxNotChangedCount = this->numberIterations / 10;
    std::uint32_t notChangedCount = 0;
    std::uint32_t iterations = 0;

    for (iterations = 0;
         (iterations < this->numberIterations) && (notChangedCount < maxNotChangedCount);
         ++iterations, ++notChangedCount)
    {
        bestTour = nearestNeighbor.run();

        tsp::TSP2opt tsp2opt(this->data, bestTour);
        tsp::TSPTour tour = tsp2opt.run();

        if (tour.getDistance() < bestTour.getDistance())
        {
            bestTour = tour;
            notChangedCount = 0;
        }
    }

    return bestTour;
}
