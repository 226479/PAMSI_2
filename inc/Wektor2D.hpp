#ifndef WEKTOR2D_HH
#define WEKTOR2D_HH

#include <iostream>


/*!
   * \brief Zestaw informacji dotyczący wektora i jego wywwolywania
   *
   * Klasa modeluje wektor o 2 wspolrzednych typu double,
   * i sposoby w jaki mają być wywolywane zawarte w nim dane
   */
class Wektor2D {
  /*
   *  Tutaj trzeba wstawic definicje odpowiednich pol i metod prywatnych
   */
  double wspolrzedne [2];// wspolrzedne[0] - x  wspolrzedne [1] - y

  public:

  double operator[ ] (int Ind) const { return wspolrzedne[Ind]; }
  double& operator[ ] (int Ind) { return wspolrzedne[Ind]; }
};


/*!
   * \brief Przeciazenie pozwala wczytac wsolrzedne wektora
   *
   *\pre Parametr \e Wek musi byc obiektem typu Wektor2D
   * \param Strm - strumien z ktorego zostana
   *wczytane wsolrzedne wektora.
   * \param Wek - wektor, ktorego wspolrzedne sa wczytywane.
   */
std::istream& operator >> (std::istream &Strm, Wektor2D &Wek);
 //std::ostream& operator << (std::ostream &Strm, Wektor2D &Wek);
/*!
   * \brief Przeciazenie pozwala wypisac wsolrzedne wektora
   *
   *\pre Parametr \e Wek musi byc obiektem typu Wektor2D
   * \param Strm - strumien z ktorego zostana
   *wypisane wsolrzedne wektora.
   * \param Wek - wektor, ktorego wspolrzedne sa wypisywane.
   */
std::ostream& operator << (std::ostream &Strm, const Wektor2D &Wek);

/*!
   * \brief Przeciazenie pozwala sumowac dwa wektory
   *
   *\pre Parametry \e Wek1 oraz \e Wek2 musza byc obiektami typu Wektor2D
   * \param Wek1 - pierwszy skladnik sumy wektorow.
   * \param Wek2 - drugi skladnik sumy wektorow.
   */
Wektor2D operator + (Wektor2D &Wek1, Wektor2D &Wek2);


/*!
   * \brief Przeciazenie pozwala odjac od siebie dwa wektory
   *
   *\pre Parametry \e Wek1 oraz \e Wek2 musza byc obiektami typu Wektor2D
   * \param Wek1 - pierwszy skladnik roznicy (odjemna) wektorow.
   * \param Wek2 - drugi skladnik roznicy (odjemnik) wektorow.
   */
Wektor2D operator - (Wektor2D &Wek1, Wektor2D &Wek2);

Wektor2D operator * (double mnoznik, Wektor2D &Wek1);


#endif
