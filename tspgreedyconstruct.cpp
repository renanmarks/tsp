#include "tspgreedyconstruct.h"
#include "tsptour.h"
#include <kdtree++/kdtree.hpp>
#include <functional>
#include <cstdlib>

tsp::TSPGreedyConstruct::TSPGreedyConstruct(const TSPLibData& _data)
    :data(_data)
{

}

tsp::TSPTour tsp::TSPGreedyConstruct::run()
{
    using Coords = tsp::TSPLibData::NodeCoordinates;
    using Tree = KDTree::KDTree<3, Coords>;

    Tree tree;
    TSPTour resultTour;

    for (auto& coord: this->data.coordinates)
    {
        tree.insert(coord);
    }

    tree.optimize();

    // First node
    std::srand(1);
    auto node = this->data.coordinates.at(std::rand() % this->data.coordinates.size());

//    while (tree.empty() == false)
    {
        auto resultTuple = tree.find_nearest(node);

        resultTour.distance += node.distance(*resultTuple.first);
        resultTour.tour.push_back(std::make_pair(node.index, resultTuple.first->index));
    }

    return resultTour;
}
