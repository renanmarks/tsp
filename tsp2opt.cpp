#include "tsp2opt.h"
#include "tsplibdistance.h"
#include <set>

tsp::TSP2opt::TSP2opt(const tsp::TSPLibData &_data, const tsp::TSPTour &_tour)
    :data(_data), originalTour(_tour)
{

}

tsp::TSPTour tsp::TSP2opt::run()
{
    using Coords = tsp::TSPLibData::NodeCoordinates;
    tsp::TSPTour newTour = this->originalTour;
    std::set<tsp::TSPTour::Edge> edges(newTour.tour.begin(), newTour.tour.end());

    std::uint32_t numberOfEdges = newTour.tour.size();
    bool changedEdges = false;

    do
    {
        changedEdges = false;

        for (std::uint32_t i = 0; i < numberOfEdges; ++i)
        {
            for (std::uint32_t j = 0; j < numberOfEdges; ++j)
            {
                if (j == i)
                {
                    continue;
                }

                // Try swap edges
                TSPTour::Edge edge0 = newTour.tour.at(i);
                TSPTour::Edge edge1 = newTour.tour.at(j);

                Coords node0 = this->data.coordinates.at(edge0.first);
                Coords node1 = this->data.coordinates.at(edge0.second);
                Coords node2 = this->data.coordinates.at(edge1.first);
                Coords node3 = this->data.coordinates.at(edge1.second);

                tsp::TSPTour::Edge newEdge0(node0.index, node3.index);
                tsp::TSPTour::Edge newEdge1(node2.index, node1.index);

                if ((edge0 == edge1) || (node0 == node3) || (node2 == node1) || (edges.find(newEdge0) != edges.end()) || (edges.find(newEdge1) == edges.end()) )
                {
                    continue;
                }

                uint32_t distanceNode01 = tsp::distanceFunctions[this->data.edgeWeightType](node0, node1);
                uint32_t distanceNode23 = tsp::distanceFunctions[this->data.edgeWeightType](node2, node3);
                uint32_t oldDistance    = distanceNode01 + distanceNode23;

                uint32_t distanceNode03 = tsp::distanceFunctions[this->data.edgeWeightType](node0, node3);
                uint32_t distanceNode21 = tsp::distanceFunctions[this->data.edgeWeightType](node2, node1);
                uint32_t newDistance    = distanceNode03 + distanceNode21;

                if (oldDistance == 0 || newDistance == 0)
                {
                    continue;
                }

                // Great! We have improvement!
                if (newDistance < oldDistance)
                {
                    newTour.tour.at(i) = newEdge0;
                    newTour.tour.at(j) = newEdge1;
                    newTour.distance -= oldDistance;
                    newTour.distance += newDistance;
                    changedEdges = true;
                }
            }
        }
    }
    while (changedEdges == true);

    return newTour;
}
