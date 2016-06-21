#include "tspcanonicaltest.h"
#include "tsplibdistance.h"

tsp::TSPCanonicalTest::TSPCanonicalTest(const TSPLibData &_data)
    : data(&_data)
{

}

tsp::TSPTour tsp::TSPCanonicalTest::run()
{
    TSPTour tour(*(this->data));

    size_t lastItem = this->data->coordinates.size()-1;
    size_t i = 0;
    size_t j = 1;

    /* Build the tour */
    for (i = 0, j = 1; j <= lastItem; ++j, ++i)
    {
        tour.insertEdge(tsp::TSPTour::Edge(i,j));
    }

    /* Close the tour */
    tour.insertEdge(tsp::TSPTour::Edge(i,0));

    return tour;
}
