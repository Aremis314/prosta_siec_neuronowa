#ifndef INICJALIZACJA_SIECI_H
#define INICJALIZACJA_SIECI_H

#include "neuron.h"

Neuron** budowaSieci(int liczbaWejsc, int liczbaWarstw, double wartoscWagi, int*& tablicaWielkosciWarstw);
Neuron* uformowanieWarstwy(double waga, double* tablicaWartosci, int liczbaWejsc, int ktoraWarstwa, int liczbaWarstw, int liczbaNeuronow, int liczbaNeuronowPoprzedniejWarstwy);
int* wpiszLiczbeNeuronow(int liczbaWarstwSieci);

#endif // INICJALIZACJA_SIECI_H
