#ifndef OBLICZANIE_BLEDU_H
#define OBLICZANIE_BLEDU_H

#include "neuron.h"

double obliczBladSieci(Neuron* siecNeuronowa, int* weryfikujacaTablica);
void zgodnoscOdpowiedzi(Neuron* siecNeuronowa, int* weryfikujacaTablica);
bool poprawnoscOdpowiedzi(Neuron* ostatniaWarstwa, int* weryfikujacaTablica);

#endif // OBLICZANIE_BLEDU_H
