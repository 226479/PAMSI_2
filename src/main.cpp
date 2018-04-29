#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>


#include "../inc/graph.hpp"


const int trams_size = 191;


int main() {

     bool end_program = 1;

     auto graph_program = std::make_unique<Graph>();

     graph_program->prepare(trams_size);

     graph_program->prepare();

     graph_program->prepare_map();

     int start_id = -1;
     int end_id = -1;

     std::cout << "Enter the starting station's id:" << std::endl;
     std::cin >> start_id;
     std::cout << "Enter the end station's id:" << std::endl;
     std::cin >> end_id;

     graph_program->run(start_id,end_id);

     std::cin >> end_program;

     return 0;
}
