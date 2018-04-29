#include <iostream>
#include <iomanip>
#include <fstream>
#include "../inc/Wektor2D.hpp"

using namespace std;

std::istream& operator >> (std::istream &Strm, Wektor2D &Wek)


 {
     cin>>Wek[0];
     cin>>Wek[1];
     return Strm;
 }

 std::ostream& operator << (std::ostream &Strm, const Wektor2D &Wek)


 {
     Strm << setw(16) << fixed << setprecision(10) <<Wek[0]<< setw(16) << fixed << setprecision(10) <<Wek[1]<<endl;
     return Strm;
 }

Wektor2D operator + (Wektor2D &Wek1, Wektor2D &Wek2)
{
    Wektor2D nowy_wektor;
    nowy_wektor[0]=Wek1[0]+Wek2[0];
    nowy_wektor[1]=Wek1[1]+Wek2[1];
    return nowy_wektor;
}

Wektor2D operator - (Wektor2D &Wek1, Wektor2D &Wek2)
{
    Wektor2D nowy_wektor;
    nowy_wektor[0]=Wek1[0]-Wek2[0];
    nowy_wektor[1]=Wek1[1]-Wek2[1];
    return nowy_wektor;
}

Wektor2D operator * (double mnoznik, Wektor2D &Wek1)
{
    Wektor2D nowy_wektor;
    nowy_wektor[0]=Wek1[0]*mnoznik;
    nowy_wektor[1]=Wek1[1]*mnoznik;
    return nowy_wektor;
}
