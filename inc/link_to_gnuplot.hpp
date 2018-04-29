#pragma once

#include <fstream>

FILE * open_gnuplot_stream();

void draw_graph( FILE * stream, char input_name_1[], char input_name_2[], char title[] );

void draw_graph( FILE * stream, char input_name[], char title[] );
