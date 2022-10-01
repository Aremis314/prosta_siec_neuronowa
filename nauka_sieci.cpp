#include "nauka_sieci.h"

void mieszajTablice(double** tablicaParametrowa, int** tablicaGatunkowa, int rozmiarTablicy) {
//    cout << "Tablica przed wymieszaniem: " << endl;
//    for(int i = 0; i < rozmiarTablicy; i++) {
//        for(int j = 0; j < liczbaParametrowIrysa; j++)
//            cout << tablica[i][j] << '\t';
//        cout << endl;
//    }

    srand(time(nullptr));
    int a = 0, b = 0;
    int bajtyParametrowegoRzedu = (liczbaParametrowIrysa + 1)*rozmiarDouble;
    int bajtyGatunkowegoRzedu = liczbaGatunkowIrysa*rozmiarInt;
    double* schowekParametrowy = new double[liczbaParametrowIrysa + 1];         // trzeba uwzględnić bias!
    int* schowekGatunkowy = new int[liczbaGatunkowIrysa];

    for(int i = 0; i < rozmiarTablicy*2; i++) {
        a = rand()%rozmiarTablicy;
        b = rand()%rozmiarTablicy;
        while(a == b)
            a = rand()%rozmiarTablicy;

        memcpy(schowekParametrowy, tablicaParametrowa[a], bajtyParametrowegoRzedu);
        memcpy(tablicaParametrowa[a], tablicaParametrowa[b], bajtyParametrowegoRzedu);
        memcpy(tablicaParametrowa[b], schowekParametrowy, bajtyParametrowegoRzedu);

        memcpy(schowekGatunkowy, tablicaGatunkowa[a], bajtyGatunkowegoRzedu);
        memcpy(tablicaGatunkowa[a], tablicaGatunkowa[b], bajtyGatunkowegoRzedu);
        memcpy(tablicaGatunkowa[b], schowekGatunkowy, bajtyGatunkowegoRzedu);

//        schowekParametrowy = tablicaParametrowa[a];
//        tablicaParametrowa[a] = tablicaParametrowa[b];
//        tablicaParametrowa[b] = schowekParametrowy;

//        schowekGatunkowy = tablicaGatunkowa[a];
//        tablicaGatunkowa[a] = tablicaGatunkowa[b];
//        tablicaGatunkowa[b] = schowekGatunkowy;
    }
    delete [] schowekParametrowy;
    delete [] schowekGatunkowy;

//    cout << "Tablica po wymieszaniu: " << endl;
//    for(int i = 0; i < rozmiarTablicy; i++) {
//        for(int j = 0; j < liczbaParametrowIrysa; j++)
//            cout << tablicaParametrowa[i][j] << '\t';
//        cout << endl;
//    }

}

void uczSiecNeuronowa(Neuron** siecNeuronowa, int liczbaWarstw, int* tablicaWielkosciWarstw, int liczbaWejsc, double wspolczynnikUczenia, double*** schowekTablicParametrowych, int*** schowekTablicGatunkowych, int* tablicaRozmiarowTablicIrysowych) {
    int licznikPetli { 0 };
    double liczbaZgodnych = 0;
    double ulamek = 0.0;
    bool niewyuczona = true;
//    double sredniNajmniejszyBladTreningowySieci { 10000.0 };
//    double sredniObecnyBladTreningowySieci { 0.0 };
//    double sredniNajmniejszyBladWalidacyjnySieci { 10000.0 };
//    double sredniObecnyBladWalidacyjnySieci { 0.0 };
    int irisTrainingArrayHandler = 0;

//    int setosa = 0;
//    int versicolor = 0;
//    int virginica = 0;

//for(int i = 0; i < tablicaRozmiarowTablicIrysowych[trybTreningowy]; i++) {
//    for(int j = 0; j < liczbaGatunkowIrysa; j ++) {
//        if(j == 0 && schowekTablicGatunkowych[trybTreningowy][i][j] == 1)
//            setosa++;
//        else if(j == 1 && schowekTablicGatunkowych[trybTreningowy][i][j] == 1)
//            versicolor++;
//        else if(j == 2 && schowekTablicGatunkowych[trybTreningowy][i][j] == 1)
//            virginica++;
//    }
//}


    while(niewyuczona) {           // sredniBladSieci > 0.1 || rozgrzanie == false

        if(licznikPetli >= 3000000) {
            cout << "Sieci nie udalo sie nauczyc wystarczajaco dobrze. Zmien parametry sieci lub sprobuj ponownie z tymi samymi! :)" << endl;
            break;
        }

        irisTrainingArrayHandler = licznikPetli % tablicaRozmiarowTablicIrysowych[trybTreningowy];
        if(licznikPetli % 10000000 == 0 && licznikPetli > 0)
            cout << licznikPetli << endl;

        if(licznikPetli % tablicaRozmiarowTablicIrysowych[trybTreningowy] == 0) {
            mieszajTablice(schowekTablicParametrowych[trybTreningowy], schowekTablicGatunkowych[trybTreningowy], tablicaRozmiarowTablicIrysowych[trybTreningowy]);

            liczbaZgodnych = 0;
            for(int i = 0; i < tablicaRozmiarowTablicIrysowych[trybTestowy]; i++) {
                nowaOdpowiedzSieci(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicParametrowych[trybTestowy][i], liczbaWejsc);
                if(poprawnoscOdpowiedzi(siecNeuronowa[liczbaWarstw - 1], schowekTablicGatunkowych[trybTestowy][i]))
                    liczbaZgodnych++;
            }
            ulamek = (liczbaZgodnych/tablicaRozmiarowTablicIrysowych[trybTestowy])*100;
//            if(ulamek >= 90.0)
//                cout << "Poprawnosc klasyfikacji danych po zakonczeniu uczenia:\t" << ulamek << '%' << endl;

            if(ulamek > 97.0) {
                liczbaZgodnych = 0;
                ulamek = 0.0;
                for(int i = 0; i < tablicaRozmiarowTablicIrysowych[trybWalidacyjny]; i++) {
                    nowaOdpowiedzSieci(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicParametrowych[trybWalidacyjny][i], liczbaWejsc);
                    if(poprawnoscOdpowiedzi(siecNeuronowa[liczbaWarstw - 1], schowekTablicGatunkowych[trybWalidacyjny][i]))
                        liczbaZgodnych++;
                }
                ulamek = (liczbaZgodnych/tablicaRozmiarowTablicIrysowych[trybTestowy])*100;
//                cout << "Poprawnosc klasyfikacji na danych walidacyjnych:\t" << ulamek << '%' << endl;

                if(ulamek > 97.0) {
                    cout << "Uczenie zakonczone. Liczba obiegow petli potrzebnych do wyuczenia sieci:\t" << licznikPetli << endl << endl;
                    niewyuczona = false;
                    continue;
                }
            }
        }


        nowaOdpowiedzSieci(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicParametrowych[trybTreningowy][irisTrainingArrayHandler], liczbaWejsc);
//        wypiszSiecWKonsoli(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicParametrowych[trybTreningowy][irisTrainingArrayHandler]);

//        sredniObecnyBladTreningowySieci += obliczBladSieci(siecNeuronowa[liczbaWarstw-1], schowekTablicGatunkowych[trybTreningowy][irisTrainingArrayHandler]);

//        if(licznikPetli % tablicaRozmiarowTablicIrysowych[trybTreningowy] == 0 && licznikPetli != 0) {
//            sredniObecnyBladTreningowySieci /= tablicaRozmiarowTablicIrysowych[trybTreningowy];
//            if(sredniObecnyBladTreningowySieci < sredniNajmniejszyBladTreningowySieci) {
//                sredniNajmniejszyBladTreningowySieci = sredniObecnyBladTreningowySieci;
//                cout << "Najmniejszy blad treningowy sieci: " << sredniNajmniejszyBladTreningowySieci << " w iteracji: " << licznikPetli << endl;
//            }
//            sredniObecnyBladTreningowySieci = 0.0;
//        }

//        if(licznikPetli % 5000 == 0) {
//            cout << "Iteracja " << licznikPetli << endl;
//            zgodnoscOdpowiedzi(siecNeuronowa[liczbaWarstw - 1], schowekTablicGatunkowych[trybTreningowy][irisTrainingArrayHandler]);
////            wypiszSiecWKonsoli(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicParametrowych[trybTreningowy][irisTrainingArrayHandler]);
//        }

        propagacjaBledu(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicGatunkowych[trybTreningowy][irisTrainingArrayHandler], schowekTablicParametrowych[trybTreningowy][irisTrainingArrayHandler], liczbaWejsc);

        poprawWagi(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicParametrowych[trybTreningowy][irisTrainingArrayHandler], liczbaWejsc, wspolczynnikUczenia);

        // poniżej 2 funkcje mające na celu sprawdzenie działania sieci bez poprawiania wag (walidacja)

        nowaOdpowiedzSieci(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, schowekTablicParametrowych[trybWalidacyjny][irisTrainingArrayHandler % tablicaRozmiarowTablicIrysowych[trybWalidacyjny]], liczbaWejsc);

//        sredniObecnyBladWalidacyjnySieci += obliczBladSieci(siecNeuronowa[liczbaWarstw-1], schowekTablicGatunkowych[trybWalidacyjny][irisTrainingArrayHandler % tablicaRozmiarowTablicIrysowych[trybWalidacyjny]]);

//        if(licznikPetli % tablicaRozmiarowTablicIrysowych[trybWalidacyjny] == 0 && licznikPetli != 0) {
//            sredniObecnyBladWalidacyjnySieci /= tablicaRozmiarowTablicIrysowych[trybWalidacyjny];
//            if(sredniObecnyBladWalidacyjnySieci < sredniNajmniejszyBladWalidacyjnySieci) {
//                sredniNajmniejszyBladWalidacyjnySieci = sredniObecnyBladWalidacyjnySieci;
//                cout << "Najmniejszy blad walidacyjny sieci: " << sredniNajmniejszyBladWalidacyjnySieci << " w iteracji: " << licznikPetli << endl;
//            }
//            sredniObecnyBladWalidacyjnySieci = 0.0;
//        }

//        if(licznikPetli % 5000 == 0)
//            zgodnoscOdpowiedzi(siecNeuronowa[liczbaWarstw - 1], schowekTablicGatunkowych[trybWalidacyjny][irisTrainingArrayHandler%tablicaRozmiarowTablicIrysowych[trybWalidacyjny]]);

//        cout << "Iteracja " << licznikPetli << endl;

        // zaimplementuj średni błąd sieci ogólny (na epokę?) oraz średni błąd sieci ostatnich 20 (10 treningowych + 10 walidacyjnych) odczytów

//        cout << endl << endl;


        licznikPetli++;

//        if(licznikPetli == 10)
//            rozgrzanie = true;
    }

}
