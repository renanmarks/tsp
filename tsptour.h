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

        using Edge = std::pair<uint32_t, uint32_t>;
        std::vector<Edge> tour;

        TSPTour();

        void print(std::ostream& out) const;
    };
}

#endif // TSPTOUR_H
