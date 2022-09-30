#include "elementy_nauki.h"

void nowaOdpowiedzSieci(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, double* wektorUczacy, int liczbaWejsc) {
    for(int i = 0; i < liczbaWarstw; i++) {
        if(i == liczbaWarstw - 1) {
            for(int j = 0; j < tablicaWielkosciWarstw[i]; j++) {            // bez - 1, bo w ostatniej warstwie nie ma biasu
                siecNeuronowa[i][j].setWartoscWyjscia(siecNeuronowa, tablicaWielkosciWarstw[i-1], i, j);
                //                for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++)
                //                    cout << siecNeuronowa[i][0].selectWagePoprzedniegoNeuronu(k) << ' ';
                //                cout << "\t" << siecNeuronowa[i][0].selectWartoscNeuronu();
                //                cout << endl << endl << endl;
            }
       }


        else {
            for(int j = 0; j < tablicaWielkosciWarstw[i] - 1; j++) {        // -1, bo nie chcemy zmieniać wartości biasu (ostatni neuron każdej ukrytej warstwy)
                if(i == 0) {
                    //                cout << "Nowy wektor uczacy: " << wektorUczacy[0] << endl;
                    siecNeuronowa[i][j].setWartoscPierwszejWarstwy(siecNeuronowa, liczbaWejsc, i, j, wektorUczacy);
                    //                for(int k = 0; k < liczbaWejsc; k++)
                    //                    cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k) << ' ';
                    //                cout << "\t" << siecNeuronowa[i][j].selectWartoscNeuronu();
                    //                cout << endl;
                }


                //             if(i == liczbaWarstw - 1) {
                //                siecNeuronowa[i][j].setWartoscWyjscia(siecNeuronowa, tablicaWielkosciWarstw[i-1], i, j);
                //                for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++)
                //                    cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k) << ' ';
                //                cout << "\t" << siecNeuronowa[i][j].selectWartoscNeuronu();
                //                cout << endl << endl << endl;
                //                continue;
                //            }


                else
                    siecNeuronowa[i][j].setWartosc(siecNeuronowa, tablicaWielkosciWarstw[i-1], i, j);
                //            for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++)
                //                cout << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k) << ' ';
                //            cout << "\t" << siecNeuronowa[i][j].selectWartoscNeuronu();
                //            cout << endl;
            }
        }
    }
}




void poprawWagi(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, double* wektorWejscia, int liczbaWejsc, double wspolczynnikUczenia) {
    double zmianaWagi { 0.0 };

    for(int i = 0; i < liczbaWarstw; i++) {
        if(i == liczbaWarstw - 1) {         // zmiana wagi ostatniej warstwy
           for(int j = 0; j < tablicaWielkosciWarstw[i]; j++) {         // bez -1, bo ostatnia warstwa nie ma biasu
                for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++) {          // w tej pętli odbywa się zamiana wag dla wszystkich połączeń danego neuronu
                    if(k == tablicaWielkosciWarstw[i-1] - 1) {          // zmiana wagi dla biasu
                        zmianaWagi = wspolczynnikUczenia * siecNeuronowa[i][j].selectWspolczynnikBledu();
                        siecNeuronowa[i][j].setWagaZTablicy(((siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) + zmianaWagi), k);
                    }


                    else {
                        zmianaWagi = wspolczynnikUczenia * siecNeuronowa[i][j].selectWspolczynnikBledu() * siecNeuronowa[i-1][k].selectWartoscNeuronu();
                        //                    cout << "Waga " << siecNeuronowa[i][0].selectWagePoprzedniegoNeuronu(k)
                        //                         << " dla warstwy " << i << " dla neuronu " << 0 << " zmienia sie o " << zmianaWagi << " do wartosci: " <<
                        //                            (siecNeuronowa[i][0].selectWagePoprzedniegoNeuronu(k)) << endl;
                        siecNeuronowa[i][j].setWagaZTablicy(((siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) + zmianaWagi), k);
                    }                   // czy pierwszy argument dobrze?
                }
            }
        }

//        ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        else {
            for(int j = 0; j < tablicaWielkosciWarstw[i] - 1; j++) {            // -1, bo nie chcemy zmieniać tablicy wag biasu (i tak bias jej nie ma)
                if(i == 0) {
                    for(int k = 0; k < liczbaWejsc; k++) {          // w tej pętli odbywa się zamiana wag dla wszystkich połączeń danego neuronu
                        if(k == liczbaWejsc - 1) {          // zmiana wagi dla biasu
                            zmianaWagi = wspolczynnikUczenia * siecNeuronowa[i][j].selectWspolczynnikBledu();
                            siecNeuronowa[i][j].setWagaZTablicy(((siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) + zmianaWagi), k);
                        }
                        else {
                            zmianaWagi = wspolczynnikUczenia * siecNeuronowa[i][j].selectWspolczynnikBledu() * wektorWejscia[k];
                            //                    cout << "Waga " << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)
                            //                         << " dla warstwy " << i << " dla neuronu " << j << " zmienia sie o " << zmianaWagi << " do wartosci: " <<
                            //                            (siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) << endl;
                            siecNeuronowa[i][j].setWagaZTablicy(((siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) + zmianaWagi), k);
                        }
                    }
                }
                else {
                    for(int k = 0; k < tablicaWielkosciWarstw[i-1]; k++) {          // w tej pętli odbywa się zamiana wag dla wszystkich połączeń danego neuronu
                        if(k == tablicaWielkosciWarstw[i-1] - 1) {          // zmiana wagi dla biasu
                            zmianaWagi = wspolczynnikUczenia * siecNeuronowa[i][j].selectWspolczynnikBledu();
                            siecNeuronowa[i][j].setWagaZTablicy(((siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) + zmianaWagi), k);
                        }
                        else {
                            zmianaWagi = wspolczynnikUczenia * siecNeuronowa[i][j].selectWspolczynnikBledu() * siecNeuronowa[i-1][k].selectWartoscNeuronu();
                            //                    cout << "Waga " << siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)
                            //                         << " dla warstwy " << i << " dla neuronu " << j << " zmienia sie o " << zmianaWagi << " do wartosci: " <<
                            //                            (siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) << endl;
                            siecNeuronowa[i][j].setWagaZTablicy(((siecNeuronowa[i][j].selectWagePoprzedniegoNeuronu(k)) + zmianaWagi), k);
                        }                   // czy pierwszy argument dobrze?
                    }
                }
            }
        }
    }
}




// propagacja zaczyna się od warstwy końcowej a kończy na warstwie nr 0

void propagacjaBledu(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, int* tablicaGatunkowa, double* tablicaParametrowa, int liczbaWejsc) {
    bool minelaPrzedostatniaWarstwa = false;
    for(int i = liczbaWarstw-1; i >= 0; i--) {
        if(i == liczbaWarstw-1) {
            for(int j = 0; j < tablicaWielkosciWarstw[i]; j++)
                wspolczynnikBleduDlaOstatniejWarstwy(siecNeuronowa, tablicaGatunkowa, tablicaWielkosciWarstw, i, j);
        }

        else {
            for(int j = 0; j < tablicaWielkosciWarstw[i] - 1; j++) {        // -1, bo nie obliczamy wsp. błędu dla biasów (ostatnich neuronów)
                wspolczynnikBleduDlaResztyWarstw(siecNeuronowa, tablicaWielkosciWarstw, i, j, tablicaParametrowa, liczbaWejsc, minelaPrzedostatniaWarstwa);
            }
        }

    }
}




void wspolczynnikBleduDlaOstatniejWarstwy(Neuron** siecNeuronowa, int* oczekiwanaOdpowiedz, int* tablicaWielkosciWarstw, int numerWarstwy, int numerNeuronu) {


    double wartoscOczekiwana = oczekiwanaOdpowiedz[numerNeuronu];

    double otrzymanaOdpowiedz = siecNeuronowa[numerWarstwy][numerNeuronu].selectWartoscNeuronu();



    double wartosciWejsc { 0.0 };
    for(int i = 0; i < tablicaWielkosciWarstw[numerWarstwy-1]; i++) {       // wyciąganie z tablicy neuronu wag i wartości poprzedników
        wartosciWejsc += siecNeuronowa[numerWarstwy][numerNeuronu].selectWagePoprzedniegoNeuronu(i) * siecNeuronowa[numerWarstwy-1][i].selectWartoscNeuronu();
    }
//    double pochodna = exp(-wartosciWejsc)/((1+exp(-wartosciWejsc))*(1+exp(-wartosciWejsc)));       // obliczanie pochodnej funkcji sigmoidalnej
    double pochodna = (1 - pow(tanh(wartosciWejsc), 2)) / 2;
//    cout << "Pochodna ostatniej warstwy: " << pochodna << endl;

//    double pochodna = 1;        // pochodna f. liniowej, a == 1.0

    double nowyWspolczynnikBledu = pochodna * (wartoscOczekiwana - otrzymanaOdpowiedz);

    siecNeuronowa[numerWarstwy][numerNeuronu].setWspolczynnikBledu(nowyWspolczynnikBledu);
}




// UWAGA DLA WARSTWY NR 0 ------ ONA BĘDZIE BRAŁA WARTOŚCI Z WEKTORA WEJŚCIA, KTÓRY NIE JEST NEURONEM!!

void wspolczynnikBleduDlaResztyWarstw(Neuron** siecNeuronowa, int* tablicaWielkosciWarstw, int numerWarstwy, int numerNeuronu, double* wektorWejscia, int liczbaWejsc, bool& czyMinelaPrzedostatniaWarstwa) {      // funkcja będzie hulała w pętli
    double wartosciWejsc { 0.0 };
    if(numerWarstwy == 0) {
        for(int i = 0; i < liczbaWejsc; i++) {          // wyciąganie z tablicy neuronu wag i wartości poprzedników dla warstwy początkowej
            wartosciWejsc += siecNeuronowa[numerWarstwy][numerNeuronu].selectWagePoprzedniegoNeuronu(i) * wektorWejscia[i];
        }
    }
    else {
        for(int i = 0; i < tablicaWielkosciWarstw[numerWarstwy-1]; i++) {       // wyciąganie z tablicy neuronu wag i wartości poprzedników
            wartosciWejsc += siecNeuronowa[numerWarstwy][numerNeuronu].selectWagePoprzedniegoNeuronu(i) * siecNeuronowa[numerWarstwy-1][i].selectWartoscNeuronu();
        }
    }
//    double pochodna = exp(-wartosciWejsc)/((1+exp(-wartosciWejsc))*(1+exp(-wartosciWejsc)));       // obliczanie pochodnej funkcji sigmoidalnej
    double pochodna = (1 - pow(tanh(wartosciWejsc), 2)) / 2;
//    cout << "Pochodna warstwy " << numerWarstwy << ": " << pochodna << endl;

//    double pochodna = 0;        // pochodna f. ReLU
//    if(wartosciWejsc <= 0)
//        pochodna = 0.1;
//    else
//        pochodna = 1;


    double sumaWagRazyWspBledu { 0.0 };
    if(tablicaWielkosciWarstw[numerWarstwy+1] - 1 == 0) {           // gdy warstwa ostatnia ma tylko jedno wyjście
        for(int i = 0; i <= tablicaWielkosciWarstw[numerWarstwy+1] - 1; i++) {       //          pobieranie wag i wsp. błędu z warstwy "młodszej" (numerWarstwy+1)
            sumaWagRazyWspBledu += siecNeuronowa[numerWarstwy+1][i].selectWagePoprzedniegoNeuronu(numerNeuronu) * siecNeuronowa[numerWarstwy+1][i].selectWspolczynnikBledu();
        }
    }

    else if(czyMinelaPrzedostatniaWarstwa == false) {
        for(int i = 0; i < tablicaWielkosciWarstw[numerWarstwy+1]; i++) {       //            pobieranie wag i wsp. błędu z warstwy "młodszej" (numerWarstwy+1)
            sumaWagRazyWspBledu += siecNeuronowa[numerWarstwy+1][i].selectWagePoprzedniegoNeuronu(numerNeuronu) * siecNeuronowa[numerWarstwy+1][i].selectWspolczynnikBledu();
        }
        if(numerNeuronu == tablicaWielkosciWarstw[numerWarstwy] - 2)
            czyMinelaPrzedostatniaWarstwa = true;
    }

    else {
        for(int i = 0; i < tablicaWielkosciWarstw[numerWarstwy+1] - 1; i++) {       // -1, bo biasu nie liczymy            pobieranie wag i wsp. błędu z warstwy "młodszej" (numerWarstwy+1)
            sumaWagRazyWspBledu += siecNeuronowa[numerWarstwy+1][i].selectWagePoprzedniegoNeuronu(numerNeuronu) * siecNeuronowa[numerWarstwy+1][i].selectWspolczynnikBledu();
        }
    }


    double nowyWspolczynnikBledu = pochodna * sumaWagRazyWspBledu;

//    cout << "Wspolczynnik bledu warstwy " << numerWarstwy << ": " << nowyWspolczynnikBledu << endl;


//    cout << siecNeuronowa[numerWarstwy][numerNeuronu].selectWspolczynnikBledu() << endl;
    siecNeuronowa[numerWarstwy][numerNeuronu].setWspolczynnikBledu(nowyWspolczynnikBledu);
//    cout << siecNeuronowa[numerWarstwy][numerNeuronu].selectWspolczynnikBledu() << endl << endl;
}
