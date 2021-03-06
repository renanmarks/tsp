#ifndef TSP2OPT_H
#define TSP2OPT_H

#include "itspalgorithm.h"
#include "tsplibdata.h"

namespace tsp
{

class TSP2opt : public ITSPAlgorithm
{
private:
    const TSPLibData* data;
    TSPTour originalTour;

public:
    TSP2opt(const TSPLibData& _data, const TSPTour& _tour);

    std::vector<TSPTour> getValidNeighbourMoves() const;

    virtual TSPTour run() override;
};

}

#endif // TSP2OPT_H
