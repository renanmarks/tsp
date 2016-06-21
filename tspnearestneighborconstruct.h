#ifndef TSPNEARESTNEIGHBORCONSTRUCT_H
#define TSPNEARESTNEIGHBORCONSTRUCT_H

#include "itspalgorithm.h"
#include "tsplibdata.h"

namespace tsp
{

class TSPNearestNeighborConstruct : public ITSPAlgorithm
{
private:
    const TSPLibData* data;

public:
    TSPNearestNeighborConstruct(const TSPLibData& _data);

    virtual TSPTour run() override;
};

}

#endif // TSPNEARESTNEIGHBORCONSTRUCT_H
