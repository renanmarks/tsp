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

        struct Edge
        {
            uint32_t first;
            uint32_t second;

            Edge() = default;
            Edge(uint32_t f, uint32_t s);
            bool isValid() const;
            Edge reverse() const;
            bool isReverseOf(const tsp::TSPTour::Edge& rhs) const;
            bool operator()(const tsp::TSPTour::Edge& rhs) const;
            bool operator< (const tsp::TSPTour::Edge& rhs) const;
            bool operator<=(const tsp::TSPTour::Edge& rhs) const;
            bool operator> (const tsp::TSPTour::Edge& rhs) const;
            bool operator>=(const tsp::TSPTour::Edge& rhs) const;
            bool operator==(const tsp::TSPTour::Edge& rhs) const;
            bool operator!=(const tsp::TSPTour::Edge& rhs) const;
        };

        std::vector<Edge> tour;

        TSPTour();

        void print(std::ostream& out) const;
    };
}


#endif // TSPTOUR_H
