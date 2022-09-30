#ifndef NOWA_ODPOWIEDZ_H
#define NOWA_ODPOWIEDZ_H

#include "neuron.h"
#include <iomanip>

void nowaOdpowiedzSieci(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, double* wektorUczacy, int liczbaWejsc);
void poprawWagi(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, double* wektorWejscia, int liczbaWejsc, double wspolczynnikUczenia);
void propagacjaBledu(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, int* tablicaGatunkowa, double* tablicaParametrowa, int liczbaWejsc);
void wspolczynnikBleduDlaOstatniejWarstwy(Neuron** siecNeuronowa, int* oczekiwanaOdpowiedz, int* tablicaWielkosciWarstw, int numerWarstwy, int numerNeuronu);
void wspolczynnikBleduDlaResztyWarstw(Neuron** siecNeuronowa, int* tablicaWielkosciWarstw, int numerWarstwy, int numerNeuronu, double* wektorWejscia, int liczbaWejsc, bool& czyMinelaPrzedostatniaWarstwa);

#endif // NOWA_ODPOWIEDZ_H
