#ifndef TSPGREEDYCONSTRUCT_H
#define TSPGREEDYCONSTRUCT_H

#include "itspalgorithm.h"
#include "tsplibdata.h"

namespace tsp
{

class TSPGreedyConstruct : public ITSPAlgorithm
{
private:
    TSPLibData data;

public:
    TSPGreedyConstruct(const TSPLibData& _data);

    virtual TSPTour run() override;
};

}

#endif // TSPGREEDYCONSTRUCT_H
