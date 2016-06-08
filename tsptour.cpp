#include "tsptour.h"

tsp::TSPTour::TSPTour()
    : distance(0)
{

}

void tsp::TSPTour::print(std::ostream &out) const
{
    out << "Distance : " << this->distance << std::endl;

//    out << "Ids : ";
//    for (const auto& id: this->tour)
//    {
//        out << id << ", ";
//    }

    out << std::endl;
}
