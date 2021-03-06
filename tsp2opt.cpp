#include "tsp2opt.h"
#include "tsplibdistance.h"
#include <algorithm>
#include <set>
#include <iostream>

tsp::TSP2opt::TSP2opt(const tsp::TSPLibData &_data, const tsp::TSPTour &_tour)
    :data(&_data), originalTour(_tour)
{

}

std::vector<tsp::TSPTour> tsp::TSP2opt::getValidNeighbourMoves() const
{
    using Coords = tsp::TSPLibData::NodeCoordinates;
    tsp::TSPTour newTour = this->originalTour;
    std::uint32_t numberOfEdges = newTour.getNumberOfEdges();
    std::vector<tsp::TSPTour::Edge> edgesOfNewTour = newTour.getEdges();

    std::vector<tsp::TSPTour> validMoves;

    validMoves.reserve(10);

    for (std::uint32_t i = 0; i < numberOfEdges; ++i)
    {
        for (std::uint32_t j = 0; j < numberOfEdges; ++j)
        {
            if (j == i)
            {
                continue;
            }

            // Try swap edges
            TSPTour::Edge edge[2] = { edgesOfNewTour.at(i), edgesOfNewTour.at(j) };

            if (edge[0].hasVertexOf(edge[1]))
            {
                continue;
            }

            Coords node[4] = { this->data->coordinates.at(edge[0].first), this->data->coordinates.at(edge[0].second),
                               this->data->coordinates.at(edge[1].first), this->data->coordinates.at(edge[1].second) };

            tsp::TSPTour::Edge newEdge[2] = { tsp::TSPTour::Edge(node[0].index, node[3].index),
                                              tsp::TSPTour::Edge(node[2].index, node[1].index) };

            if (newEdge[0].isValid() == false || newEdge[1].isValid() == false ||
                newTour.haveEdge(newEdge[0]) == true || newTour.haveEdge(newEdge[1]) == true)
            {
                continue;
            }

            newTour.eraseEdge(edge[0]);
            newTour.eraseEdge(edge[1]);
            newTour.insertEdge(newEdge[0]);
            newTour.insertEdge(newEdge[1]);

            // Error! We now have two disconnected components (cicles)!
            if (newTour.isValid() == false)
            {
                newTour.eraseEdge(newEdge[0]);
                newTour.eraseEdge(newEdge[1]);
                newTour.insertEdge(edge[0]);
                newTour.insertEdge(edge[1]);
                continue;
            }

            validMoves.push_back(newTour);
            newTour = this->originalTour;
        }
    }

    validMoves.shrink_to_fit();

    return validMoves;
}

tsp::TSPTour tsp::TSP2opt::run()
{
    using Coords = tsp::TSPLibData::NodeCoordinates;
    tsp::TSPTour newTour = this->originalTour;
    std::uint32_t numberOfEdges = newTour.getNumberOfEdges();
    bool changedEdges = false;

    do
    {
        changedEdges = false;
        std::vector<tsp::TSPTour::Edge> edgesOfNewTour = newTour.getEdges();

        for (std::uint32_t i = 0; (i < numberOfEdges) && (changedEdges == false); ++i)
        {
            for (std::uint32_t j = 0; (j < numberOfEdges) && (changedEdges == false); ++j)
            {
                if (j == i)
                {
                    continue;
                }

                // Try swap edges
                TSPTour::Edge edge[2] = { edgesOfNewTour.at(i), edgesOfNewTour.at(j) };

                if (edge[0].hasVertexOf(edge[1]))
                {
                    continue;
                }

                Coords node[4] = { this->data->coordinates.at(edge[0].first), this->data->coordinates.at(edge[0].second),
                                   this->data->coordinates.at(edge[1].first), this->data->coordinates.at(edge[1].second) };

                tsp::TSPTour::Edge newEdge[2] = { tsp::TSPTour::Edge(node[0].index, node[3].index),
                                                  tsp::TSPTour::Edge(node[2].index, node[1].index) };

                if (newEdge[0].isValid() == false || newEdge[1].isValid() == false ||
                    newTour.haveEdge(newEdge[0]) == true || newTour.haveEdge(newEdge[1]) == true)
                {
                    continue;
                }

                uint32_t distanceNode01 = tsp::distanceFunctions[this->data->edgeWeightType](node[0], node[1]);
                uint32_t distanceNode23 = tsp::distanceFunctions[this->data->edgeWeightType](node[2], node[3]);
                uint32_t oldDistance    = distanceNode01 + distanceNode23;

                uint32_t distanceNode03 = tsp::distanceFunctions[this->data->edgeWeightType](node[0], node[3]);
                uint32_t distanceNode21 = tsp::distanceFunctions[this->data->edgeWeightType](node[2], node[1]);
                uint32_t newDistance    = distanceNode03 + distanceNode21;

                if (oldDistance == 0 || newDistance == 0 || newDistance >= oldDistance)
                {
                    continue;
                }

                newTour.eraseEdge(edge[0]);
                newTour.eraseEdge(edge[1]);
                newTour.insertEdge(newEdge[0]);
                newTour.insertEdge(newEdge[1]);
                changedEdges = true;

                // Error! We now have two disconnected components (cicles)!
                if (newTour.isValid() == false)
                {
                    newTour.eraseEdge(newEdge[0]);
                    newTour.eraseEdge(newEdge[1]);
                    newTour.insertEdge(edge[0]);
                    newTour.insertEdge(edge[1]);
                    changedEdges = false;
                }
            }
        }
    }
    while (changedEdges == true);

    return newTour;
}
