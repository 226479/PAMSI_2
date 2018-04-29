#include "../inc/link_to_gnuplot.hpp"

FILE * open_gnuplot_stream()
{
    FILE * g_potok = popen( "gnuplot", "w" ); /* otwarcie potoku do zapisu */
    return g_potok;
}

void draw_graph( FILE * stream, char input_name_1[], char input_name_2[], char title[] )
{
    fprintf( stream,"set datafile separator \"%c\"\n",' ');
    fprintf( stream,"set title \"%s\"\n",title);
    fprintf( stream,"set xrange [16.865: 17.115]\n");
    fprintf( stream,"set yrange [51.060: 51.155]\n");
    fprintf( stream,"plot \'%s\' with linespoints linetype 3\n",input_name_1);
    fprintf( stream,"replot \'%s\'with linespoints lw 5 lc 5 \n",input_name_2);
}

void draw_graph( FILE * stream, char input_name[], char title[] )
{
    fprintf( stream,"set datafile separator \"%c\"\n",' ');
    fprintf( stream,"set title \"%s\"\n",title);
    fprintf( stream,"set xrange [16.865: 17.115]\n");
    fprintf( stream,"set yrange [51.060: 51.155]\n");
    fprintf( stream,"plot \'%s\' with linespoints linetype 3\n",input_name);
}
