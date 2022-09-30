#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath>

#include "odczyt_plikow.h"

using namespace std;

constexpr int trybTestowy = 2;
constexpr int trybWalidacyjny = 1;
constexpr int trybTreningowy = 0;

class Neuron
{
public:
    Neuron();
    Neuron(int liczbaWejsc);

    void setPoczatkowaWartosc(int liczbaWejsc, double waga, double* wartoscPoprzedniegoWejscia);
    void setPoczatkowaWartoscWyjscia(int liczbaWejsc, double waga, double* wartoscPoprzedniegoWejscia);
    void setWartosc(Neuron** siecNeuronowa, int liczbaWejsc, int numerWarstwy, int numerNeuronu);
    void setWartoscPierwszejWarstwy(Neuron** siecNeuronowa, int liczbaWejsc, int numerWarstwy, int numerNeuronu, double* wektorUczacy);
    void setWartoscWyjscia(Neuron** siecNeuronowa, int liczbaWejsc, int numerWarstwy, int numerNeuronu);


    void setPoczatkowaWaga(double waga);
    void setPoczatkoweTabliceWag(int liczbaWejsc, double waga);
    void setWagaZTablicy(double waga, int numerPolaczenia);

    void setWspolczynnikBledu(double nowyWspolczynnik);

    double* selectWagiWejsc();
    double selectWartoscNeuronu();
    double selectWspolczynnikBledu();
    double selectWagePoprzedniegoNeuronu(int numerNeuronu);

    ~Neuron();
private:
    double wartosc_;
    double wspolczynnikBledu_;
    double* wagaPoprzedniegoWejscia_;       // wskaźnik do tablicy z wagami neuronów z poprzedniej warstwy
};

#endif // NEURON_H
