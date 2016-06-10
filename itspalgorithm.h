#ifndef ITSPALGORITHM_H
#define ITSPALGORITHM_H

#include "tsptour.h"

namespace tsp
{
class ITSPAlgorithm
{
public:
    virtual ~ITSPAlgorithm() { }

    virtual TSPTour run() = 0;

    ITSPAlgorithm() = default;
    ITSPAlgorithm(const ITSPAlgorithm& copyFrom) = default;
    ITSPAlgorithm& operator=(const ITSPAlgorithm& copyFrom) = default;
    ITSPAlgorithm(ITSPAlgorithm &&) = default;
    ITSPAlgorithm& operator=(ITSPAlgorithm &&) = default;
};
}

#endif // ITSPALGORITHM_H
