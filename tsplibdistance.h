#ifndef TSPLIBDISTANCE_H
#define TSPLIBDISTANCE_H

#include "tsplibdata.h"

namespace tsp
{
    uint32_t roundNearestInt(double d);

    uint32_t distanceEuclidean2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);
    uint32_t distanceEuclidean3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    uint32_t distanceManhattan2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);
    uint32_t distanceManhattan3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    uint32_t distanceMaximum2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);
    uint32_t distanceMaximum3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    uint32_t distanceGeographical(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    uint32_t distancePseudoEuclidean(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);
}

#endif // TSPLIBDISTANCE_H
