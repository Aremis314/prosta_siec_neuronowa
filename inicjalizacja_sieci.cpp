#include "inicjalizacja_sieci.h"

Neuron** budowaSieci(int liczbaWejsc, int liczbaWarstw, double wartoscWagi, int*& tablicaWielkosciWarstw) {

   tablicaWielkosciWarstw = new int[liczbaWarstw];
   tablicaWielkosciWarstw = wpiszLiczbeNeuronow(liczbaWarstw);


   // teraz zostanie utworzona tablica dwuwymiarowa typu Neuron, na razie pusta --------- szkielet sieci
   // w skład szkieletu nie składa się warstwa inputów, bo nie ma ona w sobie neuronów, a tylko wektor wejścia

   Neuron** siecNeuronowa = new Neuron*[liczbaWarstw];


   double* wartoscInicjalizacyjna = new double[liczbaParametrowIrysa + 1];   // 5-ty element to bias
   for(int i = 0; i < liczbaParametrowIrysa + 1; i++)
       wartoscInicjalizacyjna[i] = 1;                // wartość tylko i wyłącznie w celach inicjalizacji sieci




   for(int i = 0; i < liczbaWarstw; i++) {

       if(i == 0) {         // wypelnianie pierwszej warstwy
           siecNeuronowa[i] = uformowanieWarstwy(wartoscWagi, wartoscInicjalizacyjna, liczbaWejsc, i, liczbaWarstw, tablicaWielkosciWarstw[i], 0);
       }

//  ---------------------------------------------------------------------------------------------------------------------------------------------------


       else if(i == liczbaWarstw-1) {        // wypelnianie ostatniej warstwy
           double* wartosciPoprzednichWejsc = new double[tablicaWielkosciWarstw[i-1]];      // tworzenie tablicy wartosci neuronow z poprzedniej warstwy
           for(int j = 0; j < tablicaWielkosciWarstw[i-1]; j++) {
               wartosciPoprzednichWejsc[j] = siecNeuronowa[i-1][j].selectWartoscNeuronu();
           }

           siecNeuronowa[i] = uformowanieWarstwy(wartoscWagi, wartosciPoprzednichWejsc, liczbaWejsc, i, liczbaWarstw, tablicaWielkosciWarstw[i], tablicaWielkosciWarstw[i-1]);
           delete [] wartosciPoprzednichWejsc;
       }

//  ---------------------------------------------------------------------------------------------------------------------------------------------------

       else {
           double* wartosciPoprzednichWejsc = new double[tablicaWielkosciWarstw[i-1]];      // wypelnianie "środkowych" warstw
           for(int j = 0; j < tablicaWielkosciWarstw[i-1]; j++) {
               wartosciPoprzednichWejsc[j] = siecNeuronowa[i-1][j].selectWartoscNeuronu();
           }

           siecNeuronowa[i] = uformowanieWarstwy(wartoscWagi, wartosciPoprzednichWejsc, liczbaWejsc, i, liczbaWarstw, tablicaWielkosciWarstw[i], tablicaWielkosciWarstw[i-1]);
           delete [] wartosciPoprzednichWejsc;
       }


   }


   delete [] wartoscInicjalizacyjna;
   return siecNeuronowa;
}




Neuron* uformowanieWarstwy(double waga, double* tablicaWartosci, int liczbaWejsc, int ktoraWarstwa, int liczbaWarstw, int liczbaNeuronow, int liczbaNeuronowPoprzedniejWarstwy) {      // liczbaWejsc będzie na początku równa ilości inputów, a potem będzie zamieniana przed końcem przebiegu pętli na ilość neuronów w aktualnej pętli




    // formowanie pierwszej warstwy

    if(ktoraWarstwa == 0) {
        Neuron* warstwaNeuronow = new Neuron[liczbaNeuronow];
        for(int i = 0; i < liczbaNeuronow - 1; i++) {       //  <-- tworzenie warstw neuronów, - 1 bo ostatni neuron to bias

            // tu funkcje z neuron.h na zmianę wartości obiektów
            warstwaNeuronow[i].setPoczatkoweTabliceWag(liczbaWejsc, waga);
            warstwaNeuronow[i].setPoczatkowaWartosc(liczbaWejsc, waga, tablicaWartosci);
//            cout << "Wartosc warstwy " << ktoraWarstwa << ": " << warstwaNeuronow[i].selectWartoscNeuronu() << endl;
        }
        return warstwaNeuronow;
    }



    // formowanie ostatniej warstwy ------ bez biasu

    if (ktoraWarstwa == liczbaWarstw-1) {
        Neuron* warstwaNeuronow = new Neuron[liczbaGatunkowIrysa];        //  <-- tworzenie warstw neuronów
        // tu funkcje z neuron.h na zmianę wartości obiektów
        for(int i = 0; i < liczbaNeuronow; i++) {
            warstwaNeuronow[i].setPoczatkoweTabliceWag(liczbaNeuronowPoprzedniejWarstwy, waga);
            warstwaNeuronow[i].setPoczatkowaWartoscWyjscia(liczbaNeuronow, waga, tablicaWartosci);
        }
//        cout << "Wartosc warstwy " << ktoraWarstwa << ": " << warstwaNeuronow[0].selectWartoscNeuronu() << endl;
        return warstwaNeuronow;

    }



    // warstwy 2, 3...

    Neuron* warstwaNeuronow = new Neuron[liczbaNeuronow];
    for(int i = 0; i < liczbaNeuronow - 1; i++) {       //  <-- tworzenie warstw neuronów, - 1 bo ostatni neuron to bias

    // tu funkcje z neuron.h na zmianę wartości obiektów
        warstwaNeuronow[i].setPoczatkoweTabliceWag(liczbaNeuronowPoprzedniejWarstwy, waga);
        warstwaNeuronow[i].setPoczatkowaWartosc(liczbaNeuronow, waga, tablicaWartosci);
    }
    return warstwaNeuronow;



}




int* wpiszLiczbeNeuronow(int liczbaWarstwSieci) {      // funkcja (1)
    string oczekiwana{};
    int* tablicaRozmiarowWarstw = new int[liczbaWarstwSieci];
    int konwertowana = 0;
    bool poprawnosc = false;

    for(int i = 0; i < liczbaWarstwSieci-1; i++) {       // -1, bo ostatnia warstwa ma z góry znaną wielkość
        poprawnosc = false;
        cout << "Wpisz liczbe neuronow dla ukrytej warstwy nr " << i+1 << ":  ";
        while(poprawnosc != true) {
            cin >> oczekiwana;
            konwertowana = stoi(oczekiwana);
            if(konwertowana < 1 || konwertowana > 20) {
                cout << "Liczba neuronow w ukrytej warstwie powinna sie miescic w przedziale <1,20>. Sprobuj wpisac liczbe jeszcze raz." << endl;
                continue;
            }
            poprawnosc = true;
        }
        tablicaRozmiarowWarstw[i] = konwertowana + 1;       // +1, bo bias jako ostatni neuron każej warstwy
    }

    tablicaRozmiarowWarstw[liczbaWarstwSieci-1] = liczbaGatunkowIrysa;

    return tablicaRozmiarowWarstw;
}
