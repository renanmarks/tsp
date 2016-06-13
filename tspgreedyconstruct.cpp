#include "tspgreedyconstruct.h"
#include "tsptour.h"
#include "tsplibdistance.h"
#include <kdtree++/kdtree.hpp>
#include <random>

tsp::TSPGreedyConstruct::TSPGreedyConstruct(const TSPLibData& _data)
    :data(_data)
{

}

using Coords = tsp::TSPLibData::NodeCoordinates;

/**
 * @brief The CoordsAccess functor
 *
 * Auxiliary to make use of the (squared difference)/10.0 bellow.
 */
struct CoordsAccess
{
   typedef double result_type;
   double operator()( Coords const& t, size_t k ) const { return t[k]; }
};

/**
 * @brief The SquaredDifferenceDiv10 functor
 *
 * Used to calculate the ATT edge weight type (Pseudo-euclidian) from TSPLIB.
 */
struct SquaredDifferenceDiv10
{
  typedef double distance_type;

  distance_type
  operator() (const double& __a, const double& __b) const
  {
    distance_type d=__a - __b;
    return static_cast<distance_type>(d*d)/static_cast<distance_type>(10.0);
  }
};

using EuclideanTree = KDTree::KDTree<2, Coords>;
using PseudoEuclideanTree = KDTree::KDTree<2, Coords, CoordsAccess, SquaredDifferenceDiv10>;

/**
 * Builds a greedy tour using the specific kdtree with specific distance function.
 */
template <typename treetype>
tsp::TSPTour
buildGreedyTour(tsp::TSPLibData& data)
{
    treetype tree;
    tsp::TSPTour resultTour;

    // Build the kdtree
    for (auto& coord: data.coordinates)
    {
        auto resultTuple = tree.find_nearest(coord,std::numeric_limits<double>::max());

        if (*resultTuple.first != coord)
        {
            tree.insert(coord);
        }
    }

    tree.optimize();

    // First node
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dist(0, data.coordinates.size()-1);

    Coords node = data.coordinates.at(dist(mt));
    Coords first = node;

    do
    {
        // Get the node off the tree...
        tree.erase(node);
        tree.optimize();

        // ... otherwise the return will be itself :)
        auto resultTuple = tree.find_nearest(node);

        if ((resultTuple.first != tree.end()) && (*resultTuple.first != node))
        {
            resultTour.distance += tsp::distanceFunctions[data.edgeWeightType](node, *resultTuple.first);
            resultTour.tour.push_back(tsp::TSPTour::Edge(node.index, resultTuple.first->index));

            node = *resultTuple.first;
        }
    }
    while (tree.empty() == false);

    // Last to first link
    resultTour.distance += tsp::distanceFunctions[data.edgeWeightType](node, first);
    resultTour.tour.push_back(tsp::TSPTour::Edge(node.index, first.index));

    return resultTour;
}

tsp::TSPTour tsp::TSPGreedyConstruct::run()
{
    if (this->data.edgeWeightType == tsp::TSPLibData::EdgeWeightType::ATT )
    {
        return buildGreedyTour<PseudoEuclideanTree>(this->data);
    }

    return buildGreedyTour<EuclideanTree>(this->data);
}
