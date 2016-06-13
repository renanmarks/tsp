#include "tsptour.h"

tsp::TSPTour::TSPTour()
    : distance(0)
{

}

void tsp::TSPTour::print(std::ostream &out) const
{
    out << "Distance : " << this->distance << std::endl;

    out << "Ids : ";
    for (const auto& pair: this->tour)
    {
        out << pair.first << "-" << pair.second << ",";
    }
    out << std::endl;
}

tsp::TSPTour::Edge::Edge(uint32_t f, uint32_t s)
    :first(f), second(s)
{

}

bool tsp::TSPTour::Edge::operator()(const tsp::TSPTour::Edge &rhs) const
{
    return (*this < rhs);
}

bool tsp::TSPTour::Edge::operator<(const tsp::TSPTour::Edge &rhs) const
{
    return (this->first < rhs.first) && (this->second < rhs.second);
}

bool tsp::TSPTour::Edge::operator<=(const tsp::TSPTour::Edge &rhs) const
{
    return (*this < rhs) || (*this == rhs);
}

bool tsp::TSPTour::Edge::operator>(const tsp::TSPTour::Edge &rhs) const
{
    return (this->first > rhs.first) && (this->second > rhs.second);
}

bool tsp::TSPTour::Edge::operator>=(const tsp::TSPTour::Edge &rhs) const
{
    return (*this > rhs) || (*this == rhs);
}

bool tsp::TSPTour::Edge::operator==(const tsp::TSPTour::Edge &rhs) const
{
    return ((this->first == rhs.first) && (this->second == rhs.second)) || ((this->first == rhs.second) && (this->second == rhs.first));
}

bool tsp::TSPTour::Edge::operator!=(const tsp::TSPTour::Edge &rhs) const
{
    return !(*this == rhs);
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
