#ifndef TSPCANONICALTEST_H
#define TSPCANONICALTEST_H

#include "itspalgorithm.h"
#include "tsplibdata.h"

namespace tsp
{
class TSPCanonicalTest : public ITSPAlgorithm
{
private:
    TSPLibData data;

public:
    TSPCanonicalTest(const TSPLibData& _data);

    virtual TSPTour run() override;
};
}

#endif // TSPCANONICALTEST_H
