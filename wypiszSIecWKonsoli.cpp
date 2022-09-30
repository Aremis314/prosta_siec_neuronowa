#include "wypiszSIecWKonsoli.h"

void wypiszSiecWKonsoli(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, double* wektorWejscia) {
    // potrzebna jest największa długość danego wiesza ---> najwieksza warstwa neuronow

    int miernikPrzestrzeniNeuronu = 0;
    int nadganiajacyMiernikPrzestrzeniNeuronu = 0;
    int liczbaCyfr = 3;
    int czystaPrzestrzenMiedzyWartosciami = 3;
    int czystaPrzestrzenMiedzyNeuronami = 6;
    int przestrzenMiedzyWartosciami = czystaPrzestrzenMiedzyWartosciami + (liczbaCyfr+1);
    int przestrzenMiedzyNeuronami = czystaPrzestrzenMiedzyNeuronami + (liczbaCyfr+1);



    cout << setprecision(liczbaCyfr - 1) << fixed << endl << endl;         // każda liczba składa się z 4 znakówE

    cout << "Wartosci wejscia: " << endl;
    for(int i = 0; i < liczbaParametrowIrysa + 1; i++)
        cout << wektorWejscia[i] << '\t';
    cout << endl << endl << endl;

    for(int i = 0; i < liczbaWarstw; i++) {
        cout << "Warstwa " << i+1 << endl;

//        w ponizszej petli zajmujemy sie wagami wiec petle z int k biora pod uwage biasy!
        if(i == liczbaWarstw - 1) {
            for(int j = 0; j < tablicaWielkosciWarstw[i]; j++) {                // pętla do wypisywania wartości wag w jednym rzędzie
                if(i == 0) {
                    for(int k = 0; k < liczbaParametrowIrysa + 1; k++) {
                        cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k);
                        cout << setw(przestrzenMiedzyWartosciami);
                    }
                    cout << setw(przestrzenMiedzyNeuronami);
                }
                else if(i == liczbaWarstw - 1) {            // ostatnia warstwa
                    for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++) {              // ostatnia warstwa nie ma biasu
                        cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k);
                        cout << setw(przestrzenMiedzyWartosciami);
                    }
                    cout << setw(przestrzenMiedzyNeuronami);
                }

                else {
                    for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++) {
                        cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k);
                        cout << setw(przestrzenMiedzyWartosciami);
                    }
                    cout << setw(przestrzenMiedzyNeuronami);
                }
            }
        }
        else {
            for(int j = 0; j < tablicaWielkosciWarstw[i] - 1; j++) {                // pętla do wypisywania wartości wag w jednym rzędzie
                if(i == 0) {
                    for(int k = 0; k < liczbaParametrowIrysa + 1; k++) {
                        cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k);
                        cout << setw(przestrzenMiedzyWartosciami);
                    }
                    cout << setw(przestrzenMiedzyNeuronami);
                }
                else if(i == liczbaWarstw - 1) {            // ostatnia warstwa
                    for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++) {              // ostatnia warstwa nie ma biasu
                        cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k);
                        cout << setw(przestrzenMiedzyWartosciami);
                    }
                    cout << setw(przestrzenMiedzyNeuronami);
                }

                else {
                    for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++) {
                        cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k);
                        cout << setw(przestrzenMiedzyWartosciami);
                    }
                    cout << setw(przestrzenMiedzyNeuronami);
                }
            }
        }
        cout << endl;






//        tu juz biasow nie bedziemy brali pod uwage

        // wartości poniżej powinny być wypisane w miarę możliwości symetrycznie na środku pod odpowiadającym zbiorem wartości wag
        if(i == 0)
            miernikPrzestrzeniNeuronu = ((liczbaCyfr+1) * (liczbaParametrowIrysa + 1)) + (czystaPrzestrzenMiedzyWartosciami*(liczbaParametrowIrysa + 1));       // należało dodać 1, bo bias
        else
            miernikPrzestrzeniNeuronu = ((liczbaCyfr+1) * tablicaWielkosciWarstw[i-1]) +  (czystaPrzestrzenMiedzyWartosciami * (tablicaWielkosciWarstw[i-1] - 1));
        nadganiajacyMiernikPrzestrzeniNeuronu = miernikPrzestrzeniNeuronu;


        if(i == liczbaWarstw - 1) {
            for(int j = 0; j < tablicaWielkosciWarstw[i]; j++) { // bez - 1, bo ostatnia warstwa nie ma biasu           // pętla do wypisywania obliczonej odpowiedzi neuronów w rzędzie pod wartościami wag
                if(j == 0) {
                    nadganiajacyMiernikPrzestrzeniNeuronu = (miernikPrzestrzeniNeuronu/2);
                    cout << setw(nadganiajacyMiernikPrzestrzeniNeuronu) << siecNeuronowa[i][j].selectWartoscNeuronu();
                    nadganiajacyMiernikPrzestrzeniNeuronu += czystaPrzestrzenMiedzyNeuronami + (miernikPrzestrzeniNeuronu/2);
                    continue;
                }
                cout << setw(nadganiajacyMiernikPrzestrzeniNeuronu) << siecNeuronowa[i][j].selectWartoscNeuronu();
            }
        }
        else {
            for(int j = 0; j < tablicaWielkosciWarstw[i] - 1; j++) {            // pętla do wypisywania obliczonej odpowiedzi neuronów w rzędzie pod wartościami wag
                if(j == 0) {
                    nadganiajacyMiernikPrzestrzeniNeuronu = (miernikPrzestrzeniNeuronu/2);
                    cout << setw(nadganiajacyMiernikPrzestrzeniNeuronu) << siecNeuronowa[i][j].selectWartoscNeuronu();
                    nadganiajacyMiernikPrzestrzeniNeuronu += czystaPrzestrzenMiedzyNeuronami + (miernikPrzestrzeniNeuronu/2);
                    continue;
                }
                cout << setw(nadganiajacyMiernikPrzestrzeniNeuronu) << siecNeuronowa[i][j].selectWartoscNeuronu();
            }
        }
        cout << endl << endl;
    }
}
