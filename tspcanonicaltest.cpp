#include "tspcanonicaltest.h"
#include "tsplibdistance.h"

tsp::TSPCanonicalTest::TSPCanonicalTest(const TSPLibData &_data)
    : data(_data)
{

}

tsp::TSPTour tsp::TSPCanonicalTest::run()
{
    TSPTour tour;

    size_t lastItem = this->data.coordinates.size()-1;
    size_t i = 0;
    size_t j = 1;

    /* Build the tour */
    for (i = 0, j = 1; j <= lastItem; ++j, ++i)
    {
        auto& c0 = this->data.coordinates.at(i);
        auto& c1 = this->data.coordinates.at(j);

        tour.distance += tsp::distanceFunctions[this->data.edgeWeightType](c0, c1);
        tour.tour.push_back(std::make_pair(i,j));
    }

    /* Close the tour */
    auto& last = this->data.coordinates.at(i);
    auto& first = this->data.coordinates.at(0);
    tour.distance += tsp::distanceFunctions[this->data.edgeWeightType](last, first);
    tour.tour.push_back(std::make_pair(i,0));

    return tour;
}
