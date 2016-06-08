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
};
}

#endif // ITSPALGORITHM_H
