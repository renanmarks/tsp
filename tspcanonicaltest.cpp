#include "tspcanonicaltest.h"
#include "tsplibdistance.h"
#include <map>
#include <iostream>

tsp::TSPCanonicalTest::TSPCanonicalTest(const TSPLibData &_data)
    : data(_data)
{

}

tsp::TSPTour tsp::TSPCanonicalTest::run()
{
    using distanceFnPtr = uint32_t (*)(const tsp::TSPLibData::NodeCoordinates&, const tsp::TSPLibData::NodeCoordinates&);

    std::map<tsp::TSPLibData::EdgeWeightType, distanceFnPtr> distanceFunctions =
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

    TSPTour tour;

    size_t lastItem = this->data.coordinates.size()-1;
    size_t i = 0;
    size_t j = 1;

    /* Build the tour */
    for (i = 0, j = 1; j <= lastItem; ++j, ++i)
    {
        auto& c0 = this->data.coordinates.at(i);
        auto& c1 = this->data.coordinates.at(j);

        tour.distance += distanceFunctions[this->data.edgeWeightType](c0, c1);
        tour.tour.push_back(std::make_pair(i,j));
    }

    /* Close the tour */
    auto& last = this->data.coordinates.at(i);
    auto& first = this->data.coordinates.at(0);
    tour.distance += distanceFunctions[this->data.edgeWeightType](last, first);
    tour.tour.push_back(std::make_pair(i,0));

    return tour;
}
