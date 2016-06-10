#ifndef TSPLIBDISTANCE_H
#define TSPLIBDISTANCE_H

#include "tsplibdata.h"
#include <map>

namespace tsp
{
    /**
     * @brief roundNearestInt
     * @param d
     * @return int(d + 0.5)
     */
    uint32_t roundNearestInt(double d);

    /**
     * @brief distanceEuclidean2D
     * @param c0
     * @param c1
     * @return Euclidean (L2-metric) distance from two 2D points.
     */
    uint32_t distanceEuclidean2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * @brief distanceEuclidean3D
     * @param c0
     * @param c1
     * @return Euclidean (L2-metric) distance from two 3D points.
     */
    uint32_t distanceEuclidean3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * @brief distanceManhattan2D
     * @param c0
     * @param c1
     * @return Manhattan (L1-metric) distance from two 2D points.
     */
    uint32_t distanceManhattan2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * @brief distanceManhattan3D
     * @param c0
     * @param c1
     * @return Manhattan (L1-metric) distance from two 3D points.
     */
    uint32_t distanceManhattan3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * @brief distanceMaximum2D
     * @param c0
     * @param c1
     * @return Manhattan (L-infinite-metric) distance from two 2D points.
     */
    uint32_t distanceMaximum2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * @brief distanceMaximum3D
     * @param c0
     * @param c1
     * @return Manhattan (L-infinite-metric) distance from two 3D points.
     */
    uint32_t distanceMaximum3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * @brief distanceGeographical
     * @param c0
     * @param c1
     * @return Geographical (Earth spheric radius based) distance from two points.
     */
    uint32_t distanceGeographical(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * @brief distancePseudoEuclidean
     * @param c0
     * @param c1
     * @return "Pseudo-Euclidean" distance from two points.
     */
    uint32_t distancePseudoEuclidean(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1);

    /**
     * Distance function pointer.
     */
    using distanceFnPtr = uint32_t (*)(const tsp::TSPLibData::NodeCoordinates&, const tsp::TSPLibData::NodeCoordinates&);

    /**
     * Dictionary of edge weight type's to respective distance functions.
     */
    static std::map<tsp::TSPLibData::EdgeWeightType, distanceFnPtr> distanceFunctions =
    {
        {tsp::TSPLibData::EdgeWeightType::EUC_2D, tsp::distanceEuclidean2D     },
        {tsp::TSPLibData::EdgeWeightType::EUC_3D, tsp::distanceEuclidean3D     },
        {tsp::TSPLibData::EdgeWeightType::MAN_2D, tsp::distanceManhattan2D     },
        {tsp::TSPLibData::EdgeWeightType::MAN_3D, tsp::distanceManhattan3D     },
        {tsp::TSPLibData::EdgeWeightType::MAX_2D, tsp::distanceMaximum2D       },
        {tsp::TSPLibData::EdgeWeightType::MAX_3D, tsp::distanceMaximum3D       },
        {tsp::TSPLibData::EdgeWeightType::GEO,    tsp::distanceGeographical    },
        {tsp::TSPLibData::EdgeWeightType::ATT,    tsp::distancePseudoEuclidean }
    };
}

#endif // TSPLIBDISTANCE_H
