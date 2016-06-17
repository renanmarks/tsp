#include "tsptour.h"
#include "tsplibdistance.h"
#include <algorithm>
#include <iostream>

tsp::TSPTour::TSPTour(const TSPLibData &_data)
    : distance(0), numberOfEdges(0), data(_data)
{
    this->adjacencyList.resize(_data.coordinates.size());
}

void tsp::TSPTour::insertEdge(const tsp::TSPLibData::NodeCoordinates &first, const tsp::TSPLibData::NodeCoordinates &second)
{
    auto listBegin = this->adjacencyList.cbegin();
    auto listEnd = this->adjacencyList.cend();

    if ((listBegin + first.index >= listEnd) || (listBegin + second.index >= listEnd))
    {
        return;
    }

    auto& list1 = this->adjacencyList.at(first.index);
    auto& list2 = this->adjacencyList.at(second.index);
    list1.push_back(second.index);
    list2.push_back(first.index);
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    std::uint32_t distance = tsp::distanceFunctions[this->data.edgeWeightType](first, second);

    this->setDistance(this->getDistance() + distance);
    ++(this->numberOfEdges);
}

void tsp::TSPTour::insertEdge(const tsp::TSPTour::Edge &edge)
{
    const auto& first = this->data.coordinates.at(edge.first);
    const auto& second = this->data.coordinates.at(edge.second);

    this->insertEdge(first, second);
}

void tsp::TSPTour::eraseEdge(const tsp::TSPLibData::NodeCoordinates &first, const tsp::TSPLibData::NodeCoordinates &second)
{
    auto listBegin = this->adjacencyList.cbegin();
    auto listEnd = this->adjacencyList.cend();

    if ((listBegin + first.index == listEnd) || (listBegin + second.index > listEnd))
    {
        return;
    }

    auto& list  = this->adjacencyList.at(first.index);
    auto& list2 = this->adjacencyList.at(second.index);
    auto it     = std::find(std::begin(list), std::end(list), second.index);
    auto it2    = std::find(std::begin(list2), std::end(list2), first.index);

    if (it != list.end())
    {
        list.erase(it);
        std::sort(list.begin(), list.end());
    }

    if (it2 != list2.end())
    {
        list2.erase(it2);
        std::sort(list2.begin(), list2.end());
    }

    std::uint32_t distance = tsp::distanceFunctions[this->data.edgeWeightType](first, second);

    this->setDistance(this->getDistance() - distance);
    --(this->numberOfEdges);
}

void tsp::TSPTour::eraseEdge(const tsp::TSPTour::Edge &edge)
{
    const auto& first = this->data.coordinates.at(edge.first);
    const auto& second = this->data.coordinates.at(edge.second);

    this->eraseEdge(first, second);
}

bool tsp::TSPTour::haveEdge(const tsp::TSPLibData::NodeCoordinates &first, const tsp::TSPLibData::NodeCoordinates &second) const
{
    return this->haveEdge(tsp::TSPTour::Edge(first.index, second.index));
}

bool tsp::TSPTour::haveEdge(const tsp::TSPTour::Edge &edge) const
{
    const auto& list1 = this->adjacencyList.at(edge.first);
    const auto& list2 = this->adjacencyList.at(edge.second);

    const auto it1 = std::find(list1.begin(), list1.end(), edge.second);
    const auto it2 = std::find(list2.begin(), list2.end(), edge.first);

    bool oneway = (it1 != list1.end());
    bool otherway = (it2 != list2.end());

    return oneway && otherway;
}

std::size_t tsp::TSPTour::getNumberOfEdges() const
{
    return this->numberOfEdges;
}

tsp::TSPTour::Edge tsp::TSPTour::getEdge(const std::size_t index) const
{
    return this->getEdges().at(index);
}

std::vector<tsp::TSPTour::Edge> tsp::TSPTour::getEdges() const
{
    std::vector<std::vector<bool>> adjacencyMatrix;
    std::vector<Edge> returnEdges;
    std::size_t numberOfVertices = this->adjacencyList.size();

    returnEdges.reserve(this->numberOfEdges);
    adjacencyMatrix.resize(numberOfVertices);

    for (auto& line : adjacencyMatrix)
    {
        line.resize(numberOfVertices);
    }

    for (std::uint32_t first = 0; first < this->adjacencyList.size(); first++)
    {
        const auto& list = this->adjacencyList.at(first);

        for (std::uint32_t second : list)
        {
            Edge edge(first, second);

            if (edge.isValid() &&
                    adjacencyMatrix[first][second] == false &&
                    adjacencyMatrix[second][first] == false)
            {
                adjacencyMatrix[first][second] = true;
                adjacencyMatrix[second][first] = true;

                returnEdges.push_back(edge);
            }
        }
    }

    return returnEdges;
}

std::uint32_t tsp::TSPTour::getDistance() const
{
    return distance;
}

void tsp::TSPTour::setDistance(const std::uint32_t &value)
{
    distance = value;
}

void tsp::TSPTour::print(std::ostream &out) const
{
    out << "Distance : " << this->distance << std::endl;

    out << "Edges(" << this->getNumberOfEdges() << ") : ";
    for (const auto& pair: this->getEdges())
    {
        out << pair << ",";
    }
    out << std::endl;
}

tsp::TSPTour::Edge::Edge(std::uint32_t f, std::uint32_t s)
    :first(f), second(s)
{

}

bool tsp::TSPTour::Edge::operator==(const tsp::TSPTour::Edge &rhs) const
{
    return ((this->first == rhs.first) && (this->second == rhs.second)) || ((this->first == rhs.second) && (this->second == rhs.first));
}

bool tsp::TSPTour::Edge::operator!=(const tsp::TSPTour::Edge &rhs) const
{
    return !(*this == rhs);
}

std::ostream & tsp::operator<<(std::ostream &os, const tsp::TSPTour::Edge &e)
{
    os << e.first << "-" << e.second;

    return os;
}

bool tsp::TSPTour::Edge::isValid() const
{
    return this->first != this->second;
}

tsp::TSPTour::Edge tsp::TSPTour::Edge::reverse() const
{
    return Edge(this->second, this->first);
}

bool tsp::TSPTour::Edge::isReverseOf(const tsp::TSPTour::Edge &rhs) const
{
    return *this == rhs.reverse();
}

bool tsp::TSPTour::Edge::hasVertexOf(const tsp::TSPTour::Edge &rhs) const
{
    return this->first == rhs.first || this->first == rhs.second || this->second == rhs.first || this->second == rhs.second;
}
