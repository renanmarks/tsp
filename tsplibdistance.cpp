#include <cmath>
#include "tsplibdistance.h"

uint32_t tsp::roundNearestInt(double d)
{
    return static_cast<uint32_t>(d+0.5);
}

uint32_t tsp::distanceEuclidean2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    double xd = c0.coordinate.at(0) - c1.coordinate.at(0);
    double yd = c0.coordinate.at(1) - c1.coordinate.at(1);

    return tsp::roundNearestInt(std::sqrt(xd*xd +  yd*yd));
}

uint32_t tsp::distanceEuclidean3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    double xd = c0.coordinate.at(0) - c1.coordinate.at(0);
    double yd = c0.coordinate.at(1) - c1.coordinate.at(1);
    double zd = c0.coordinate.at(2) - c1.coordinate.at(2);

    return tsp::roundNearestInt(std::sqrt(xd*xd +  yd*yd + zd*zd));
}

uint32_t tsp::distanceManhattan2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    double xd = std::abs(c0.coordinate.at(0) - c1.coordinate.at(0));
    double yd = std::abs(c0.coordinate.at(1) - c1.coordinate.at(1));

    return tsp::roundNearestInt(xd + yd);
}

uint32_t tsp::distanceManhattan3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    double xd = std::abs(c0.coordinate.at(0) - c1.coordinate.at(0));
    double yd = std::abs(c0.coordinate.at(1) - c1.coordinate.at(1));
    double zd = std::abs(c0.coordinate.at(2) - c1.coordinate.at(2));

    return tsp::roundNearestInt(xd + yd + zd);
}

uint32_t tsp::distanceMaximum2D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    double xd = std::abs(c0.coordinate.at(0) - c1.coordinate.at(0));
    double yd = std::abs(c0.coordinate.at(1) - c1.coordinate.at(1));

    return std::max(tsp::roundNearestInt(xd), tsp::roundNearestInt(yd));
}

uint32_t tsp::distanceMaximum3D(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    double xd = std::abs(c0.coordinate.at(0) - c1.coordinate.at(0));
    double yd = std::abs(c0.coordinate.at(1) - c1.coordinate.at(1));
    double zd = std::abs(c0.coordinate.at(2) - c1.coordinate.at(2));
    uint32_t max_xy = std::max(tsp::roundNearestInt(xd), tsp::roundNearestInt(yd));
    uint32_t max_xyz = std::max(max_xy, tsp::roundNearestInt(zd));

    return max_xyz;
}

uint32_t tsp::distanceGeographical(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    //TODO: Implement Geographical distance!
    return 0;
}

uint32_t tsp::distancePseudoEuclidean(const tsp::TSPLibData::NodeCoordinates& c0, const tsp::TSPLibData::NodeCoordinates& c1)
{
    double xd = c0.coordinate.at(0) - c1.coordinate.at(0);
    double yd = c0.coordinate.at(1) - c1.coordinate.at(1);
    double rij = std::sqrt( (xd*xd + yd*yd) / 10.0 );
    uint32_t tij = tsp::roundNearestInt(rij);

    if (tij < rij)
    {
        return tij + 1;
    }

    return tij;
}
