#ifndef TSPTOUR_H
#define TSPTOUR_H

#include <cstdint>
#include <vector>
#include <ostream>
#include "tsplibdistance.h"

namespace tsp
{
    class TSPTour
    {
    private:
        std::uint32_t distance;
        std::size_t numberOfEdges;
        const tsp::TSPLibData* data;
        using AdjacencyList = std::vector<std::vector<std::uint32_t>>;
        AdjacencyList adjacencyList;

    public:

        struct Edge
        {
            std::uint32_t first;
            std::uint32_t second;

            Edge() = default;
            Edge(std::uint32_t f, std::uint32_t s);
            bool isValid() const;
            Edge reverse() const;
            bool isReverseOf(const tsp::TSPTour::Edge& rhs) const;
            bool hasVertexOf(const tsp::TSPTour::Edge& rhs) const;
            bool operator() (const tsp::TSPTour::Edge& rhs) const;
            bool operator== (const tsp::TSPTour::Edge& rhs) const;
            bool operator!= (const tsp::TSPTour::Edge& rhs) const;

        };

        TSPTour(const tsp::TSPLibData& _data);

        void insertEdge(const tsp::TSPLibData::NodeCoordinates& first, const tsp::TSPLibData::NodeCoordinates& second);
        void insertEdge(const Edge& edge);

        void eraseEdge(const tsp::TSPLibData::NodeCoordinates& first, const tsp::TSPLibData::NodeCoordinates& second);
        void eraseEdge(const Edge& edge);

        bool haveEdge(const tsp::TSPLibData::NodeCoordinates& first, const tsp::TSPLibData::NodeCoordinates& second) const;
        bool haveEdge(const Edge& edge) const;

        bool isValid() const;

        std::size_t getNumberOfEdges() const;
        Edge getEdge(const std::size_t i) const;
        std::vector<Edge> getEdges() const;

        void print(std::ostream& out) const;

        std::uint32_t getDistance() const;
        void setDistance(const std::uint32_t &value);

        bool operator== (const tsp::TSPTour& rhs) const;
        bool operator!= (const tsp::TSPTour& rhs) const;
    };

    std::ostream& operator<<(std::ostream& os, const tsp::TSPTour::Edge& e);
}


#endif // TSPTOUR_H
