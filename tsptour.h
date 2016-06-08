#ifndef TSPTOUR_H
#define TSPTOUR_H

#include <cstdint>
#include <vector>
#include <ostream>

namespace tsp
{
    struct TSPTour
    {
        uint32_t distance;
        std::vector<uint32_t> tour;

        TSPTour();

        void print(std::ostream& out) const;
    };
}

#endif // TSPTOUR_H
