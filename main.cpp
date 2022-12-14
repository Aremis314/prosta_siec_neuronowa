#include "odczyt_plikow.h"
#include "inicjalizacja_sieci.h"
#include "nauka_sieci.h"

using namespace std;


int main()
{
    bool niepoprawnoscDanych = false;
    string irysTrening {"iris_training.dat"};
    string irysWalidacja {"iris_validation.dat"};
    string irysTest {"iris_test.dat"};
    int liczbaWejsc { 5 };
    int liczbaWarstw = wczytywanieIlosciWarstw(niepoprawnoscDanych);
    double wagaPoczatkowa = wczytywaniePoczatkowejWagi(niepoprawnoscDanych);
    double wspolczynnikUczenia = wczytywanieWspolczynnikaUczenia(niepoprawnoscDanych);
    int* tablicaWielkosciWarstw { nullptr };
    Neuron** siecNeuronowa { nullptr };
    double** treningTablicaParametrowaIrysow { nullptr };
    double** walidacjaTablicaParametrowaIrysow { nullptr };
    double** testTablicaParametrowaIrysow { nullptr };
    int** treningTablicaGatunkowaIrysow { nullptr };
    int** walidacjaTablicaGatunkowaIrysow { nullptr };
    int** testTablicaGatunkowaIrysow { nullptr };
    int rozmiarTreningowejTablicyIrysow = wczytanieDanychIrysow(treningTablicaParametrowaIrysow, treningTablicaGatunkowaIrysow, irysTrening, niepoprawnoscDanych);
    int rozmiarWalidacyjnejTablicyIrysow = wczytanieDanychIrysow(walidacjaTablicaParametrowaIrysow, walidacjaTablicaGatunkowaIrysow, irysWalidacja, niepoprawnoscDanych);
    int rozmiarTestowejTablicyIrysow = wczytanieDanychIrysow(testTablicaParametrowaIrysow, testTablicaGatunkowaIrysow, irysTest, niepoprawnoscDanych);

    if(niepoprawnoscDanych)
        cout << "Koniec programu w wyniku bledu podczas wczytywania danych z pliku..." << endl << endl;

    else {
        double*** schowekTablicParametrowych = new double**[3];
        schowekTablicParametrowych[trybTreningowy] = treningTablicaParametrowaIrysow;
        schowekTablicParametrowych[trybWalidacyjny] = walidacjaTablicaParametrowaIrysow;
        schowekTablicParametrowych[trybTestowy] = testTablicaParametrowaIrysow;

        int*** schowekTablicGatunkowych = new int**[3];
        schowekTablicGatunkowych[trybTreningowy] = treningTablicaGatunkowaIrysow;
        schowekTablicGatunkowych[trybWalidacyjny] = walidacjaTablicaGatunkowaIrysow;
        schowekTablicGatunkowych[trybTestowy] = testTablicaGatunkowaIrysow;

        int schowekRozmiarowTablicIrysow[3] = {rozmiarTreningowejTablicyIrysow, rozmiarWalidacyjnejTablicyIrysow, rozmiarTestowejTablicyIrysow};





        siecNeuronowa = budowaSieci(liczbaWejsc, liczbaWarstw, wagaPoczatkowa, tablicaWielkosciWarstw);

        cout << "Siec zostala zbudowana." << endl << endl;

        uczSiecNeuronowa(siecNeuronowa, liczbaWarstw, tablicaWielkosciWarstw, liczbaWejsc, wspolczynnikUczenia, schowekTablicParametrowych, schowekTablicGatunkowych, schowekRozmiarowTablicIrysow);






        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < schowekRozmiarowTablicIrysow[i]; j++) {
                delete [] schowekTablicParametrowych[i][j];
                delete [] schowekTablicGatunkowych[i][j];
            }
            delete [] schowekTablicParametrowych[i];
            delete [] schowekTablicGatunkowych[i];
        }
        delete [] schowekTablicParametrowych;
        delete [] schowekTablicGatunkowych;

        for(int i = 0; i < liczbaWarstw; i++)
            delete [] siecNeuronowa[i];
        delete [] siecNeuronowa;

        delete [] tablicaWielkosciWarstw;
    }



    return 0;
}
