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
    virtual ~TSPCanonicalTest() = default;

    virtual TSPTour run() override;

    TSPCanonicalTest() = default;
    TSPCanonicalTest(const TSPCanonicalTest& copyFrom) = default;
    TSPCanonicalTest& operator=(const TSPCanonicalTest& copyFrom) = default;
    TSPCanonicalTest(TSPCanonicalTest &&) = default;
    TSPCanonicalTest& operator=(TSPCanonicalTest &&) = default;
};
}

#endif // TSPCANONICALTEST_H
