#include "obliczanie_bledu.h"

double obliczBladSieci(Neuron* siecNeuronowa, int* weryfikujacaTablica) {
    double komponent = 0;
    for(int i = 0; i < liczbaGatunkowIrysa; i++) {
        komponent += abs(double(weryfikujacaTablica[i]) - siecNeuronowa[i].selectWartoscNeuronu());
    }
    komponent /= 3; //pow(liczbaGatunkowIrysa, 2);


    return komponent;


}

void zgodnoscOdpowiedzi(Neuron* siecNeuronowa, int* weryfikujacaTablica) {
    cout << "Poprawne: ";
    for(int i = 0; i < liczbaGatunkowIrysa; i++) {
        cout << weryfikujacaTablica[i] << " ";
}
    cout << "\tObliczone: ";
    for(int i = 0; i < liczbaGatunkowIrysa; i++) {
        cout << siecNeuronowa[i].selectWartoscNeuronu() << " ";
    }
    cout << endl;
}

bool poprawnoscOdpowiedzi(Neuron* ostatniaWarstwa, int* weryfikujacaTablica) {
    int index = 0;
    double max { 0.0 };
    for(int i = 0; i < liczbaGatunkowIrysa; i++) {
        if(i == 0) {
            max = ostatniaWarstwa[i].selectWartoscNeuronu();
            continue;
        }

        if(max < ostatniaWarstwa[i].selectWartoscNeuronu()) {
            max = ostatniaWarstwa[i].selectWartoscNeuronu();
            index = i;
        }
    }
    max = 1.0;

    if(max == weryfikujacaTablica[index])
        return true;
    else
        return false;
}
