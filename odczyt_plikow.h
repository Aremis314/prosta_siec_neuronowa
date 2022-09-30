#ifndef WCZYTYWANIE_ILOSCI_WARSTW_H
#define WCZYTYWANIE_ILOSCI_WARSTW_H

#include <fstream>
#include <iostream>

using namespace std;

constexpr int liczbaParametrowIrysa = 4;         // there are 4 distincted iris' parameters in files
constexpr int liczbaGatunkowIrysa = 3;            // from available data we are able to classify 3 species of iris

int wczytywanieIlosciWarstw();
double wczytywaniePoczatkowejWagi();
double wczytywanieWspolczynnikaUczenia();
int wczytanieDanychIrysow(double**& IrParam, int**& IrSpec, string plik);

#endif // WCZYTYWANIE_ILOSCI_WARSTW_H
