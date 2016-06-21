#ifndef TSPGRASP_H
#define TSPGRASP_H

#include "itspalgorithm.h"
#include <memory>

namespace tsp
{

class TSPGrasp : public ITSPAlgorithm
{
private:
    const tsp::TSPLibData* data;
    std::uint32_t numberIterations;

public:
    TSPGrasp(const tsp::TSPLibData& _data, std::uint32_t _numberIterations);

    // ITSPAlgorithm interface
public:
    virtual TSPTour run() override;
};

}

#endif // TSPGRASP_H
