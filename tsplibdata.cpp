#include <istream>
#include <regex>
#include <iostream>
#include <sstream>
#include "tsplibdata.h"
#include "tsplibdistance.h"

/* Only local to this translation unit */
namespace {

void fillSpecs(tsp::TSPLibData& data, std::smatch& matches)
{
    using Type = tsp::TSPLibData;

    if (matches[1] == "NAME")
    {
        data.name = matches[2];
    }
    else if (matches[1] == "TYPE")
    {
        if (matches[2] == "TSP")       data.type = Type::DataType::TSP;
        else if (matches[2] == "ATSP") data.type = Type::DataType::ATSP;
        else if (matches[2] == "SOP")  data.type = Type::DataType::SOP;
        else if (matches[2] == "HCP")  data.type = Type::DataType::HCP;
        else if (matches[2] == "CVRP") data.type = Type::DataType::CVRP;
        else if (matches[2] == "TOUR") data.type = Type::DataType::TOUR;
    }
    else if (matches[1] == "COMMENT")
    {
        data.comment = matches[2];
    }
    else if (matches[1] == "DIMENSION")
    {
        std::stringstream stream(matches[2]);
        stream >> data.dimension;

        if (data.type == Type::DataType::TSP || data.type == Type::DataType::ATSP)
        {
            data.coordinates.resize(data.dimension);
        }
        //TODO: implement the "dimmension" for other types, if necessary
    }
    else if (matches[1] == "CAPACITY")
    {
        std::stringstream stream(matches[2]);
        stream >> data.capacity;
    }
    else if (matches[1] == "EDGE_WEIGHT_TYPE")
    {
        if      (matches[2] == "EXPLICIT") { data.edgeWeightType = Type::EdgeWeightType::EXPLICIT; }
        else if (matches[2] == "EUC_2D")   { data.edgeWeightType = Type::EdgeWeightType::EUC_2D; data.nodeCoordenatesType = Type::NodeCoordenatesType::TWOD_COORDS; }
        else if (matches[2] == "EUC_3D")   { data.edgeWeightType = Type::EdgeWeightType::EUC_3D; data.nodeCoordenatesType = Type::NodeCoordenatesType::THREED_COORDS; }
        else if (matches[2] == "MAX_2D")   { data.edgeWeightType = Type::EdgeWeightType::MAX_2D; }
        else if (matches[2] == "MAX_3D")   { data.edgeWeightType = Type::EdgeWeightType::MAX_3D; }
        else if (matches[2] == "MAN_2D")   { data.edgeWeightType = Type::EdgeWeightType::MAN_2D; }
        else if (matches[2] == "MAN_3D")   { data.edgeWeightType = Type::EdgeWeightType::MAN_3D; }
        else if (matches[2] == "CEIL_2D")  { data.edgeWeightType = Type::EdgeWeightType::CEIL_2D; }
        else if (matches[2] == "GEO")      { data.edgeWeightType = Type::EdgeWeightType::GEO; }
        else if (matches[2] == "ATT")      { data.edgeWeightType = Type::EdgeWeightType::ATT; data.nodeCoordenatesType = Type::NodeCoordenatesType::TWOD_COORDS; }
        else if (matches[2] == "XRAY1")    { data.edgeWeightType = Type::EdgeWeightType::XRAY1; }
        else if (matches[2] == "XRAY2")    { data.edgeWeightType = Type::EdgeWeightType::XRAY2; }
        else if (matches[2] == "SPECIAL")  { data.edgeWeightType = Type::EdgeWeightType::SPECIAL; }
    }
    else if (matches[1] == "EDGE_WEIGHT_FORMAT")
    {
        if      (matches[2] == "FUNCTION")       data.edgeWeightFormat = Type::EdgeWeightFormat::FUNCTION;
        else if (matches[2] == "FULL_MATRIX")    data.edgeWeightFormat = Type::EdgeWeightFormat::FULL_MATRIX;
        else if (matches[2] == "UPPER_ROW")      data.edgeWeightFormat = Type::EdgeWeightFormat::UPPER_ROW;
        else if (matches[2] == "LOWER_ROW")      data.edgeWeightFormat = Type::EdgeWeightFormat::LOWER_ROW;
        else if (matches[2] == "UPPER_DIAG_ROW") data.edgeWeightFormat = Type::EdgeWeightFormat::UPPER_DIAG_ROW;
        else if (matches[2] == "LOWER_DIAG_ROW") data.edgeWeightFormat = Type::EdgeWeightFormat::LOWER_DIAG_ROW;
        else if (matches[2] == "UPPER_COL")      data.edgeWeightFormat = Type::EdgeWeightFormat::UPPER_COL;
        else if (matches[2] == "LOWER_COL")      data.edgeWeightFormat = Type::EdgeWeightFormat::LOWER_COL;
        else if (matches[2] == "UPPER_DIAG_COL") data.edgeWeightFormat = Type::EdgeWeightFormat::UPPER_DIAG_COL;
        else if (matches[2] == "LOWER_DIAG_COL") data.edgeWeightFormat = Type::EdgeWeightFormat::LOWER_DIAG_COL;
    }
    else if (matches[1] == "EDGE_DATA_FORMAT")
    {
        if      (matches[2] == "EDGE_LIST")   data.edgeDataFormat = Type::EdgeDataFormat::EDGE_LIST;
        else if (matches[2] == "ADJ_LIST")    data.edgeDataFormat = Type::EdgeDataFormat::ADJ_LIST;
    }
    else if (matches[1] == "NODE_COORD_TYPE")
    {
        if      (matches[2] == "NO_COORDS")     data.nodeCoordenatesType = Type::NodeCoordenatesType::NO_COORDS;
        else if (matches[2] == "TWOD_COORDS")   data.nodeCoordenatesType = Type::NodeCoordenatesType::TWOD_COORDS;
        else if (matches[2] == "THREED_COORDS") data.nodeCoordenatesType = Type::NodeCoordenatesType::THREED_COORDS;
    }
    else if (matches[1] == "DISPLAY_DATA_TYPE")
    {
        if      (matches[2] == "COORD_DISPLAY") data.displayDataType = Type::DisplayDataType::COORD_DISPLAY;
        else if (matches[2] == "TWOD_DISPLAY")  data.displayDataType = Type::DisplayDataType::TWOD_DISPLAY;
        else if (matches[2] == "NO_DISPLAY")    data.displayDataType = Type::DisplayDataType::NO_DISPLAY;
    }

    return;
}

bool parseSpec(tsp::TSPLibData& data, const std::string& fileLine)
{
    /* Matches all the specification tags*/
    std::regex specsRegex("^(.+) ?: ?(\\b.+)$");
    std::smatch specsMatches;

    /* Regex search */
    std::regex_search(fileLine, specsMatches, specsRegex);

    if (specsMatches.ready() && specsMatches.empty() && specsMatches.size() == 0)
    {
        return true;
    }

    fillSpecs(data, specsMatches);

    return false;
}

bool parseData(tsp::TSPLibData& data, const std::string& fileLine, std::istream& file)
{
    /* Matches all the specification tags*/
    std::regex specsRegex("^\\s*(.*_SECTION):?\\s*$");
    std::smatch specsMatches;

    /* Regex search */
    std::regex_search(fileLine, specsMatches, specsRegex);

    if (specsMatches.ready() && specsMatches.empty() && specsMatches.size() == 0)
    {
        return true;
    }

    if (specsMatches[1] == "NODE_COORD_SECTION")
    {
        int index = 0;
        std::string dataLine;
        using d = tsp::TSPLibData;

        std::getline(file, dataLine);

        while (file.good() && dataLine != "EOF")
        {
            std::istringstream sstream(dataLine);
            double x = 0.0;
            double y = 0.0;
            double z = 0.0;
            sstream >> index;  --index;
            sstream >> x >> y;

            if (data.nodeCoordenatesType == d::NodeCoordenatesType::THREED_COORDS)
            {
                sstream >> z;
            }

            data.coordinates.at(index) = d::NodeCoordinates(index, x, y, z);
            std::getline(file, dataLine);
        }
    }

    return false;
}

}

void tsp::TSPLibData::load(std::istream &file)
{
    std::string fileLine;
    bool endOfHeader = false;

    while (file.good() && endOfHeader == false)
    {
        std::getline(file, fileLine);

        /* Quits loop when found a data keyword */
        endOfHeader = parseSpec(*this, fileLine);
    }

    parseData(*this, fileLine, file);

    //TODO: parse the data section
}

tsp::TSPLibData::NodeCoordinates::NodeCoordinates(int64_t i, double x, double y, double z)
    : index(i), coordinate({x, y, z})
{

}

tsp::TSPLibData::NodeCoordinates::value_type tsp::TSPLibData::NodeCoordinates::operator[](size_t i) const
{
    return this->coordinate.at(i);
}

bool tsp::TSPLibData::NodeCoordinates::operator==(const NodeCoordinates& other) const
{
    return (this->coordinate[0] == other[0]) && (this->coordinate[1] == other[1]) && (this->coordinate[2] == other[2]) && (this->index == other.index);
}

bool tsp::TSPLibData::NodeCoordinates::operator!=(const NodeCoordinates& other) const
{
    return !(*this == other);
}
