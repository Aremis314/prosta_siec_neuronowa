#include "neuron.h"

Neuron::Neuron() {
    wartosc_ = 1;           // bo ostatni neuron ukrytych warstw nie będzie modyfikowany, bo będzie biasem
    wspolczynnikBledu_ = 0;
    wagaPoprzedniegoWejscia_ = nullptr;
}

Neuron::Neuron(int liczbaWejsc) {
    wartosc_ = 1;           // bo ostatni neuron ukrytych warstw nie będzie modyfikowany, bo będzie biasem
    wspolczynnikBledu_ = 0;
    wagaPoprzedniegoWejscia_ = new double[liczbaWejsc];
}

void Neuron::setPoczatkowaWartosc(int liczbaWejsc, double waga, double* wartoscPoprzedniegoWejscia) {
    double sumaWazona = 0;
    for(int q = 0; q < liczbaWejsc; q++) {
        sumaWazona += waga*wartoscPoprzedniegoWejscia[q];
    }
//     wartosc_ = 1/(1+exp(-sumaWazona));        // f. sigmoidalna

    wartosc_ = (tanh(sumaWazona) + 1) / 2;


     //f. ReLU

//     if(sumaWazona < 0)
//         wartosc_ = 0.1*sumaWazona;
//     else
//         wartosc_ = sumaWazona;
}

void Neuron::setPoczatkowaWartoscWyjscia(int liczbaWejsc, double waga, double* wartoscPoprzedniegoWejscia) {
    double sumaWazona = 0;
    for(int q = 0; q < liczbaWejsc; q++) {
        sumaWazona += waga*wartoscPoprzedniegoWejscia[q];
    }
//    wartosc_ = 1/(1+exp(-sumaWazona));
    wartosc_ = (tanh(sumaWazona) + 1) / 2;
//    wartosc_ = sumaWazona;          // f. liniowa, a == 1.0
}

void Neuron::setWartosc(Neuron** siecNeuronowa, int liczbaWejsc, int numerWarstwy, int numerNeuronu) {
    double sumaWazona = 0;
    for(int q = 0; q < liczbaWejsc; q++) {
        sumaWazona += siecNeuronowa[numerWarstwy][numerNeuronu].selectWagePoprzedniegoNeuronu(q) * siecNeuronowa[numerWarstwy-1][q].selectWartoscNeuronu();
    }
//    wartosc_ = 1/(1+exp(-sumaWazona));        // f. sigmoidalna
    wartosc_ = (tanh(sumaWazona) + 1) / 2;


    //f. ReLU

//    if(sumaWazona < 0)
//        wartosc_ = 0.1*sumaWazona;
//    else
//        wartosc_ = sumaWazona;
}

void Neuron::setWartoscPierwszejWarstwy(Neuron** siecNeuronowa, int liczbaWejsc, int numerWarstwy, int numerNeuronu, double* wektorUczacy) {
    double sumaWazona = 0;
    for(int q = 0; q < liczbaWejsc; q++) {
        sumaWazona += siecNeuronowa[numerWarstwy][numerNeuronu].selectWagePoprzedniegoNeuronu(q) * wektorUczacy[q];
    }
//    wartosc_ = 1/(1+exp(-sumaWazona));        // f. sigmoidalna
    wartosc_ = (tanh(sumaWazona) + 1) / 2;


    //f. ReLU

//    if(sumaWazona < 0)
//        wartosc_ = 0.1*sumaWazona;
//    else
//        wartosc_ = sumaWazona;
}

void Neuron::setWartoscWyjscia(Neuron** siecNeuronowa, int liczbaWejsc, int numerWarstwy, int numerNeuronu) {
    double sumaWazona = 0;
    for(int q = 0; q < liczbaWejsc; q++) {
        sumaWazona += siecNeuronowa[numerWarstwy][numerNeuronu].selectWagePoprzedniegoNeuronu(q) * siecNeuronowa[numerWarstwy-1][q].selectWartoscNeuronu();
    }
//    wartosc_ = 1/(1+exp(-sumaWazona));        // f. sigmoidalna
    wartosc_ = (tanh(sumaWazona) + 1) / 2;


//    wartosc_ = sumaWazona;          // f. liniowa, a == 1.0
}


void Neuron::setPoczatkoweTabliceWag(int liczbaWejsc, double waga) {
    wagaPoprzedniegoWejscia_ = new double[liczbaWejsc];
    for(int q = 0; q < liczbaWejsc; q++){
        wagaPoprzedniegoWejscia_[q] = waga;
    }
}

void Neuron::setWagaZTablicy(double waga, int numerPolaczenia) {
    wagaPoprzedniegoWejscia_[numerPolaczenia] = waga;
}

void Neuron::setWspolczynnikBledu(double nowyWspolczynnik) {
    wspolczynnikBledu_ = nowyWspolczynnik;
}

double Neuron::selectWartoscNeuronu() {
    return wartosc_;
}


double Neuron::selectWspolczynnikBledu() {
    return wspolczynnikBledu_;
}


double Neuron::selectWagePoprzedniegoNeuronu(int numerNeuronu){
    return wagaPoprzedniegoWejscia_[numerNeuronu];
}


Neuron::~Neuron() {
}
