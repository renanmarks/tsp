#include "tsp2opt.h"
#include "tspnearestneighborconstruct.h"
#include "tsptabu.h"
#include <queue>
#include <algorithm>

tsp::TSPTabu::TSPTabu(const TSPLibData &_data, uint32_t _numberIterations, size_t _tabuListSize, int32_t _incumbentCost)
    : data(_data), numberIterations(_numberIterations), tabuListSize(_tabuListSize), incumbentCost(_incumbentCost)
{

}

tsp::TSPTour tsp::TSPTabu::run()
{
    // TODO: Build better architecture :)
    std::deque<tsp::TSPTour> tabuList;
    tsp::TSPNearestNeighborConstruct nearestNeighbor(this->data);
    tsp::TSPTour bestTour = nearestNeighbor.run();

    std::uint32_t maxNotChangedCount = this->numberIterations;
    std::uint32_t notChangedCount = 0;
    std::uint32_t iterations = 0;

    for (iterations = 0;
         (iterations < this->numberIterations) && (notChangedCount < maxNotChangedCount);
         ++iterations, ++notChangedCount)
    {
        tsp::TSP2opt tsp2opt(this->data, bestTour);
        auto neighbourMoves = tsp2opt.getValidNeighbourMoves();
        std::uint32_t cost = 0;

        for (const tsp::TSPTour& move : neighbourMoves )
        {
            auto found = std::find(tabuList.begin(), tabuList.end(), move);

            if (found == tabuList.end() && move.getDistance() < bestTour.getDistance())
            {
                bestTour = move;
                maxNotChangedCount = 0;
            }
            else
            {
                cost = bestTour.getDistance() - (bestTour.getDistance() - found->getDistance());

                if ( (cost < this->incumbentCost) && (found->getDistance() > bestTour.getDistance()) )
                {
                    bestTour = move;
                    maxNotChangedCount = 0;
                }
            }
        }

        tabuList.push_back(bestTour);

        if (tabuList.size() > this->tabuListSize)
        {
            tabuList.pop_front();
        }
    }

    return bestTour;
}
