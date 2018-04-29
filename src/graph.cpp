#include <iostream>
#include <cstring>
#include <queue>
#include <chrono>
#include <thread>
#include <cmath>


#include "../inc/graph.hpp"
#include "../inc/link_to_gnuplot.hpp"


void Graph::run(const int& start_id, const int& end_id) {
    bool tmp1, tmp2 = false;

    auto start_station = std::make_shared<Station>();
    auto end_station = std::make_shared<Station>();
    auto my_road1 = std::make_shared<std::stack<std::shared_ptr<Station>>>();
    auto my_road2 = std::make_shared<std::stack<std::shared_ptr<Station>>>();
    auto my_road3 = std::make_shared<std::stack<std::shared_ptr<Station>>>();

    FILE *gnupotok1 = open_gnuplot_stream();
    FILE *gnupotok2 = open_gnuplot_stream();
    FILE *gnupotok3 = open_gnuplot_stream();

    std::ofstream export_my_road_BFS;
    std::ofstream export_my_road_DFS;
    std::ofstream export_my_road_ASTAR;

    std::list<std::shared_ptr<Station>>::iterator iter;
    for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++)
    {
        if ((*iter)->id == start_id) {
            std::cout << (*iter)->id << std::endl;
            std::cout << "Find 1st Station's ID" << std::endl;
            start_station = (*iter);
            tmp1 = true;
        }
        if ((*iter)->id == end_id) {
            std::cout << (*iter)->id << std::endl;
            std::cout << "Find 2st Station's ID" << std::endl;
            end_station = (*iter);
            tmp2 = true;
        }
    }
    if (!tmp1 || !tmp2)
    {
        std::cout << "Invalid Station's ID " << tmp1 << " " << tmp2 << std::endl;
    }
    else
    {
        breth_first_search(start_station,end_station,my_road1,gnupotok1,export_my_road_BFS);
        export_my_road_BFS.open("../data_trams/exportmyroadBFS.dat");
        while (!(*my_road1).empty())
        {
            export_my_road_BFS << (*my_road1).top()->localization[0] << " " << (*my_road1).top()->localization[1] << std::endl;
            (*my_road1).pop();
        }
        draw_graph(gnupotok1, "../data_trams/mapa.dat", "../data_trams/exportmyroadBFS.dat", "BFS");
        fflush(gnupotok1);


        deep_first_search(start_station,end_station,my_road2,gnupotok2,export_my_road_DFS);
        export_my_road_DFS.open("../data_trams/exportmyroadDFS.dat");
        while (!(*my_road2).empty())
        {
            export_my_road_DFS << (*my_road2).top()->localization[0] << " " << (*my_road2).top()->localization[1] << std::endl;
            (*my_road2).pop();
        }
        draw_graph(gnupotok2, "../data_trams/mapa.dat", "../data_trams/exportmyroadDFS.dat", "DFS");
        fflush(gnupotok2);


        astar(start_station, end_station, my_road3, gnupotok3, export_my_road_ASTAR);
        export_my_road_ASTAR.open("../data_trams/exportmyroadASTAR.dat");
        while (!(*my_road3).empty())
        {
            export_my_road_ASTAR << (*my_road3).top()->localization[0] << " " << (*my_road3).top()->localization[1] << std::endl;
            (*my_road3).pop();
        }
        draw_graph(gnupotok3, "../data_trams/mapa.dat", "../data_trams/exportmyroadASTAR.dat", "ASTAR");
        fflush(gnupotok3);

        export_my_road_BFS.close();
        export_my_road_DFS.close();
        export_my_road_ASTAR.close();
    }
}

void Graph::prepare(const int& size)
{
    for (int _input_file = 1; _input_file < size; ++_input_file)
    {
        std::string input_path = "../data_trams/" + std::to_string(_input_file) + ".csv";
        std::ifstream tram_file(input_path);

        if (tram_file.is_open())
        {
            std::string buffer, line_name, station_name, street_name;
            int  time, id;
            bool already_exists;

            std::shared_ptr<Station> acctual, next;

            getline(tram_file, line_name);

            while (!tram_file.eof())
            {
                getline(tram_file,buffer,',');
                id = atoi(buffer.c_str());

                getline(tram_file,buffer,',');
                station_name = buffer;

                getline(tram_file,buffer,',');
                street_name = buffer;

                getline(tram_file,buffer,',');

                already_exists = false;

                std::list<std::shared_ptr<Station>>::iterator iter;
                for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++)
                {
                    if((*iter)->station_name == station_name)
                    {
                        acctual = *iter;
                        already_exists = true;
                        break;
                    }
                }
                if(!already_exists)
                {
                    this->station_list.push_back(std::make_shared<Station>());
                    acctual=*(--(this->station_list.end()));
                    acctual->station_name = station_name;
                    acctual->id = id;
                    acctual->street_name = station_name;
                }
                do
                {
                    getline(tram_file,buffer,',');
                    id = atoi(buffer.c_str());

                    getline(tram_file, buffer, ',');
                    station_name = buffer;

                    getline(tram_file, buffer, ',');
                    street_name = buffer;

                    getline(tram_file, buffer, ',');
                    time = atoi(buffer.c_str());

                    already_exists = false;

                    for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++)
                    {
                        if((*iter)->station_name == station_name)
                        {
                            next = *iter;
                            already_exists = true;
                            break;
                        }
                    }

                    if(!already_exists)
                    {
                        this->station_list.push_back(std::make_shared<Station>());
                        next = *(--(this->station_list.end()));
                        next->station_name = station_name;
                        next->id = id;
                        next->street_name = station_name;
                    }

                    acctual->neighbors_list.push_back(std::make_shared<Connection>());

                    (*(--(acctual->neighbors_list.end())))->adjacent_station = next;
                    (*(--(acctual->neighbors_list.end())))->travel_time = time;
                    (*(--(acctual->neighbors_list.end())))->tram_name = line_name;

                    acctual=next;
                }
                while (!tram_file.eof());
                if(!tram_file.eof())
                {
                    getline(tram_file,buffer);
                    acctual = nullptr;
                    next = nullptr;
                }
            }
            tram_file.close();
        } else
        {
            std::cerr << "Unable to open file contain tram's data" << std::endl;
        }
    }
}

 void Graph::prepare()
 {
     std::ifstream location_file("../data_trams/coordinates.csv");

     if (location_file.is_open())
     {
         std::string buffer;
         double x,y;
         int id;
         getline(location_file, buffer);
         while (!location_file.eof())
         {
             getline(location_file,buffer, ';');
             x = atof(buffer.c_str());

             getline(location_file,buffer, ';');
             y = atof(buffer.c_str());

             getline(location_file,buffer, ';');
             id = atoi(buffer.c_str());

             getline(location_file,buffer);

             std::list<std::shared_ptr<Station>>::iterator iter;
             for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++)
             {
                 if((*iter)->id==id)
                 {
                     (*iter)->localization[0] = x;
                     (*iter)->localization[1] = y;
                     break;
                 }
             }
         }
         location_file.close();
     }
     else
     {
         std::cerr << "Unable to open file contain coordinates" << std::endl;
     }
 }

 Graph::~Graph()
 {
 }

 void Graph::prepare_map()
 {
     std::ofstream map;
     map.open("../data_trams/mapa.dat");

     std::list<std::shared_ptr<Station>>::iterator iter;
     for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++)
     {
         if((*iter)->localization[0] != 0 && (*iter)->localization[1] != 0)
         {
             std::list<std::shared_ptr<Connection>>::iterator iter2;
             for ( iter2 = (*iter)->neighbors_list.begin(); iter2 != (*iter)->neighbors_list.end(); iter2++)
             {
                 if((*iter2)->adjacent_station->localization[0] != 0 && (*iter2)->adjacent_station->localization[1] != 0)
                 {
                     map << (*iter2)->adjacent_station->localization[0] << " " << (*iter2)->adjacent_station->localization[1] << std::endl;
                     map << (*iter)->localization[0] << " " << (*iter)->localization[1] << std::endl << std::endl;
                 }
             }
         }
     }
     map.close();
 }

void Graph::breth_first_search(std::shared_ptr<Station> start_station,
                               std::shared_ptr<Station> end_station,
                               std::shared_ptr<std::stack < std::shared_ptr<Station> >> my_road,
                               FILE * stream,
                               std::ofstream &export_my_road)
{
    int time_to_end_station = 0;
    int extensions = 0;

    std::list < std::shared_ptr < Station >> ::iterator iter;
    for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++ )
    {
        (*iter)->color = 0;
    }

    start_station->color = 1;

    std::queue <std::shared_ptr<Station>> station_queue;
    std::shared_ptr <Station> u;
    station_queue.push(start_station);

//    auto start = std::chrono::high_resolution_clock::now();

    while (!station_queue.empty())
    {
        u = station_queue.front();
        station_queue.pop();
        if (u == end_station)
        {

            while (u != start_station)
            {
                time_to_end_station += u->time_to_parent;
                (*my_road).push(u);
                u = u->search_parent;
            }
            (*my_road).push(start_station);
            break;
        }
        std::list < std::shared_ptr < Connection >> ::iterator iter2;
        for (iter2= (u->neighbors_list.begin()); iter2 != (u->neighbors_list.end()); iter2++ )
        {
            if ((*iter2)->adjacent_station->color == 0)
            {
                (*iter2)->adjacent_station->color = 1;
                (*iter2)->adjacent_station->search_parent= u;
                (*iter2)->adjacent_station->time_to_parent = ((*iter2)->travel_time);
                (*iter2)->adjacent_station->search_tram_to_parent = ((*iter2)->tram_name);
                station_queue.push((*iter2)->adjacent_station);
            }
        }

        extensions++;

        u->color = 3;

        (*my_road).push(u);
        while (u != start_station)
        {
            (*my_road).push(u);
            u = u->search_parent;
        }
        (*my_road).push(start_station);

        std::ofstream my_road_ex;
        my_road_ex.open("../data_trams/exportmyroadBFS.dat");

        while (!(*my_road).empty())
        {
            my_road_ex << (*my_road).top()->localization[0] << " " << (*my_road).top()->localization[1] << std::endl;
            (*my_road).pop();
        }
        my_road_ex.close();

        draw_graph(stream, "../data_trams/mapa.dat", "../data_trams/exportmyroadBFS.dat", "BFS");
        fflush( stream );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

    }

//    auto finish = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "czas: " << time_to_end_station << std::endl;
//    std::cout << extensions << std::endl;
//    std::cout.precision(10);
//    std::cout << elapsed.count() << std::endl;
}


void Graph::deep_first_search(std::shared_ptr<Station> start_station,
                              std::shared_ptr<Station> end_station,
                              std::shared_ptr<std::stack < std::shared_ptr<Station> >> my_road,
                              FILE * stream,
                              std::ofstream &export_my_road)
{
    int time_to_end_station=0;
    int extensions=0;

    std::list < std::shared_ptr < Station >> ::iterator iter;
    for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++ )
    {
        (*iter)->color = 0;
    }

    start_station->color = 1;

    std::stack<std::shared_ptr<Station>> station_stack;
    std::shared_ptr<Station> u;
    station_stack.push(start_station);

//    auto start = std::chrono::high_resolution_clock::now();

    while (!station_stack.empty())
    {
        u=station_stack.top();
        station_stack.pop();
        if(u==end_station)
        {
            while(u!=start_station)
            {
                time_to_end_station+=u->time_to_parent;
                (*my_road).push(u);
                u=u->search_parent;
            }
            (*my_road).push(start_station);
            break;
        }

        std::list<std::shared_ptr<Connection>>::iterator iter2;
        for(iter2 =(u->neighbors_list.begin()); iter2 != (u->neighbors_list.end()); iter2++ )
        {
            if ((*iter2)->adjacent_station->color == 0)
            {
                (*iter2)->adjacent_station->color = 1;
                (*iter2)->adjacent_station->search_parent = u ;
                (*iter2)->adjacent_station->time_to_parent = (*iter2)->travel_time;
                (*iter2)->adjacent_station->search_tram_to_parent = (*iter2)->tram_name;
                station_stack.push((*iter2)->adjacent_station);
            }
        }

        extensions++;

        u->color = 3;

        (*my_road).push(u);
        while(u!=start_station)
        {
            (*my_road).push(u);
            u=u->search_parent;
        }
        (*my_road).push(start_station);
        std::ofstream my_road_ex;
        my_road_ex.open("../data_trams/exportmyroadDFS.dat");

        while (!(*my_road).empty())
        {
            my_road_ex << (*my_road).top()->localization[0] << " " << (*my_road).top()->localization[1] << std::endl;
            (*my_road).pop();
        }
        my_road_ex.close();

        draw_graph(stream, "../data_trams/mapa.dat", "../data_trams/exportmyroadDFS.dat", "DFS");
        fflush( stream );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

    }
//    auto finish = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "czas: " << time_to_end_station << std::endl;
//    std::cout << extensions << std::endl;
//    std::cout.precision(10);
//    std::cout << elapsed.count() << std::endl;
}

void Graph::astar(std::shared_ptr<Station> start_station, std::shared_ptr<Station> end_station,
                  std::shared_ptr<std::stack<std::shared_ptr<Station> >> my_road, FILE *stream,
                  std::ofstream &export_my_road)
{
    int time_to_end_station = 0;
    int extensions = 0;

    std::list<std::shared_ptr<Station>>::iterator iter;
    for (iter = this->station_list.begin(); iter != this->station_list.end(); iter++)
    {
        (*iter)->color = 0;
    }

    start_station->color =1;

    std::list<std::shared_ptr<Station>> station_list;
    std::shared_ptr<Station> u, w;
    station_list.push_front(start_station);

//    auto start = std::chrono::high_resolution_clock::now();

    while (!station_list.empty())
    {
        u = station_list.front();
        u->searchWektorToEndStation = u->localization - end_station->localization;
        u->metersToEndStation = sqrt(u->searchWektorToEndStation[0] * u->searchWektorToEndStation[0] +
                                     u->searchWektorToEndStation[1] * u->searchWektorToEndStation[1]) * 300;
        w = u;
        while (w != start_station)
        {
            w->searchWektorToParent = w->localization - w->search_parent->localization;
            w->searchDistanceToParent = sqrt(w->searchWektorToParent[0] * w->searchWektorToParent[0] +
                                             w->searchWektorToParent[1] * w->searchWektorToParent[1]);
            u->accumulateDistance += w->searchDistanceToParent;

            w = w->search_parent;
        }

        auto takeThisOutOfMyList = station_list.begin();

        std::list<std::shared_ptr<Station>>::iterator iter2;
        for (iter2 = station_list.begin(); iter2 != station_list.end(); iter2++)
        {
            if (((*iter2)->metersToEndStation + (*iter2)->accumulateDistance) <
                (u->metersToEndStation + u->accumulateDistance)) {
                u = (*iter2);
                takeThisOutOfMyList = iter2;
            }
        }

        station_list.erase(takeThisOutOfMyList);
        if (u == end_station)
        {
            while (u != start_station)
            {
                time_to_end_station += u->time_to_parent;
                (*my_road).push(u);
                u = u->search_parent;
            }
            (*my_road).push(start_station);
            break;
        }

        std::list<std::shared_ptr<Connection >>::iterator iter3;
        for (iter3 = (u->neighbors_list.begin()); iter3 != (u->neighbors_list.end()); iter3++)
        {
            if ((*iter3)->adjacent_station->color == 0)
            {
                (*iter3)->adjacent_station->color = 1;
                (*iter3)->adjacent_station->search_parent = u;
                (*iter3)->adjacent_station->time_to_parent = ((*iter3)->travel_time);
                (*iter3)->adjacent_station->search_tram_to_parent = ((*iter3)->tram_name);

                (*iter3)->adjacent_station->searchWektorToEndStation =
                        (*iter3)->adjacent_station->localization - end_station->localization;
                (*iter3)->adjacent_station->metersToEndStation =
                        sqrt((*iter3)->adjacent_station->searchWektorToEndStation[0] *
                             (*iter3)->adjacent_station->searchWektorToEndStation[0] +
                             (*iter3)->adjacent_station->searchWektorToEndStation[1] *
                             (*iter3)->adjacent_station->searchWektorToEndStation[1]) * 300;
                w = (*iter3)->adjacent_station;
                while (w != start_station)
                {
                    w->searchWektorToParent = w->localization - w->search_parent->localization;
                    w->searchDistanceToParent = sqrt(w->searchWektorToParent[0] * w->searchWektorToParent[0] +
                                                     w->searchWektorToParent[1] * w->searchWektorToParent[1]);
                    (*iter3)->adjacent_station->accumulateDistance += w->searchDistanceToParent;
                    w = w->search_parent;
                }
                station_list.push_front((*iter3)->adjacent_station);
            }
        }
        extensions++;

        u->color = 3;

        (*my_road).push(u);
        while (u != start_station)
        {
            (*my_road).push(u);
            u = u->search_parent;
        }
        (*my_road).push(start_station);

        std::ofstream my_road_ex;
        my_road_ex.open("../data_trams/exportmyroadASTAR.dat");

        while (!(*my_road).empty())
        {
            my_road_ex << (*my_road).top()->localization[0] << " " << (*my_road).top()->localization[1] << std::endl;
            (*my_road).pop();
        }

        my_road_ex.close();

        draw_graph(stream, "../data_trams/mapa.dat", "../data_trams/exportmyroadASTAR.dat", "ASTAR");
        fflush( stream );

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
//    auto finish = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double> elapsed = finish - start;

    std::cout << "czas: " << time_to_end_station << std::endl;
//    std::cout << extensions << std::endl;
//    std::cout.precision(10);
//    std::cout << elapsed.count() << std::endl;
}
