#pragma once


#include <fstream>
#include <memory>
#include <list>
#include <stack>


#include "insterfaces.hpp"
#include "station.hpp"


class Graph : public IRunnable, public IPreparable
{
    std::list<std::shared_ptr<Station>> station_list;

    void breth_first_search(std::shared_ptr<Station> start_station,
                            std::shared_ptr<Station> end_station,
                            std::shared_ptr<std::stack < std::shared_ptr<Station> >> my_road,
                            FILE * stream,
                            std::ofstream &export_my_road);

    void deep_first_search(std::shared_ptr<Station> start_station,
                           std::shared_ptr<Station> end_station,
                           std::shared_ptr<std::stack < std::shared_ptr<Station> >> my_road,
                           FILE * stream,
                           std::ofstream &export_my_road);

    void astar(std::shared_ptr<Station> start_station,
               std::shared_ptr<Station> end_station,
               std::shared_ptr<std::stack < std::shared_ptr<Station> >> my_road,
               FILE * stream,
               std::ofstream &export_my_road);

public:

    ~Graph();

    void run(const int& start_id, const int& end_id) override;

    void prepare(const int& size) override;

    void prepare() override;

    void prepare_map() override;

};
