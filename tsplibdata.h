#ifndef TSPLIBDATA_H
#define TSPLIBDATA_H

#include <array>
#include <cstdint>
#include <istream>
#include <map>
#include <string>
#include <vector>

class TSPLibData
{
public:
    std::string name;

    enum class DataType
    {
        TSP,  // Symmetric TSP
        ATSP, // Asymmetric TSP
        SOP,  // Seq. Ordering Problem
        HCP,  // Hamiltonian Cycle
        CVRP, // Capacitated Vehicle Routing Problem
        TOUR  // Collection of tours
    };

    DataType type;
    std::string comment;

    std::int32_t dimension;
    std::int32_t capacity;

    enum class EdgeWeightType
    {
        EXPLICIT, // Weights are listed explicitly in the corresponding section
        EUC_2D,   // Weights are Euclidean distances in 2-D
        EUC_3D,   // Weights are Euclidean distances in 3-D
        MAX_2D,   // Weights are maximum distances in 2-D
        MAX_3D,   // Weights are maximum distances in 3-D
        MAN_2D,   // Weights are Manhattan distances in 2-D
        MAN_3D,   // Weights are Manhattan distances in 3-D
        CEIL_2D,  // Weights are Euclidean distances in 2-D rounded up
        GEO,      // Weights are geographical distances
        ATT,      // Special distance function for problems att48 and att532
        XRAY1,    // Special distance function for crystallography problems (Version 1)
        XRAY2,    // Special distance function for crystallography problems (Version 2)
        SPECIAL   // There is a special distance function documented elsewhere
    };

    EdgeWeightType edgeWeightType;

    enum class EdgeWeightFormat
    {
        FUNCTION,       // Weights are given by a function (see above)
        FULL_MATRIX,    // Weights are given by a full matrix
        UPPER_ROW,      // Upper triangular matrix (row-wise without diagonal entries)
        LOWER_ROW,      // Lower triangular matrix (row-wise without diagonal entries)
        UPPER_DIAG_ROW, // Upper triangular matrix (row-wise including diagonal entries)
        LOWER_DIAG_ROW, // Lower triangular matrix (row-wise including diagonal entries)
        UPPER_COL,      // Upper triangular matrix (column-wise without diagonal entries)
        LOWER_COL,      // Lower triangular matrix (column-wise without diagonal entries)
        UPPER_DIAG_COL, // Upper triangular matrix (column-wise including diagonal entries)
        LOWER_DIAG_COL  // Lower triangular matrix (column-wise including diagonal entries)
    };

    EdgeWeightFormat edgeWeightFormat;

    enum class EdgeDataFormat
    {
        EDGE_LIST, // The graph is given by an edge list
        ADJ_LIST   // The graph is given as an adjacency list
    };

    EdgeDataFormat edgeDataFormat;

    enum class NodeCoordenatesType
    {
        NO_COORDS,    // The nodes do not have associated coordinates - DEFAULT
        TWOD_COORDS,  // Nodes are specified by coordinates in 2-D
        THREED_COORDS // Nodes are specified by coordinates in 3-D
    };

    NodeCoordenatesType nodeCoordenatesType;

    enum class DisplayDataType
    {
        COORD_DISPLAY, // Display is generated from the node coordinates
        TWOD_DISPLAY,  // Explicit coordinates in 2-D are given
        NO_DISPLAY     // No graphical display is possible
    };

    DisplayDataType displayDataType;

    struct NodeCoordinates
    {
        std::array<double, 3> coordinate;
    };

    std::vector<NodeCoordinates> coordinates;

    /* Methods */

    TSPLibData();

};

#endif // TSPLIBDATA_H
