#ifndef NAUKA_SIECI_H
#define NAUKA_SIECI_H

#include "elementy_nauki.h"
#include "obliczanie_bledu.h"
#include "wypiszSIecWKonsoli.h"


// dla 64-bit
constexpr int rozmiarDouble = 8;
constexpr int rozmiarInt = 4;

void mieszajTablice(double** tablicaParametrowa, int** tablicaGatunkowa, int rozmiarPrzykladuUczacego);
void uczSiecNeuronowa(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, int liczbaWejsc, double wspolczynnikUczenia, double*** schowekTablicParametrowych, int*** schowekTablicGatunkowych, int* tablicaRozmiarowTablicIrysowych);

#endif // NAUKA_SIECI_H
