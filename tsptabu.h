#ifndef TSPTABU_H
#define TSPTABU_H

#include "itspalgorithm.h"


namespace tsp
{

class TSPTabu : public ITSPAlgorithm
{
private:
    const tsp::TSPLibData* data;
    std::uint32_t numberIterations;
    std::size_t tabuListSize;
    std::int32_t incumbentCost;

public:
    TSPTabu(const tsp::TSPLibData& _data, std::uint32_t _numberIterations, size_t _tabuListSize, int32_t _incumbentCost);

    // ITSPAlgorithm interface
public:
    TSPTour run();
};

}

#endif // TSPTABU_H
