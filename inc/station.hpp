#pragma once


#include <string>
#include <list>
#include <memory>


#include "Wektor2D.hpp"


class Connection;


class Station {

public:

    std::string station_name;
    std::string street_name;
    std::string search_tram_to_parent;

    int id;
    int color;
    int time_to_parent;

    std::shared_ptr<Station> search_parent=nullptr;

    Wektor2D localization;
    Wektor2D searchWektorToParent;
    Wektor2D searchWektorToEndStation;

    double searchDistanceToParent=0;
    double accumulateDistance=0;
    double metersToEndStation=0;

    std::list<std::shared_ptr<Connection>> neighbors_list;

};


class Connection {

public:

    std::string tram_name;

    int travel_time;

    std::shared_ptr<Station> adjacent_station;

};
