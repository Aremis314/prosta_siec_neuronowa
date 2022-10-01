#include "odczyt_plikow.h"

int wczytywanieIlosciWarstw(bool& niepoprawnoscDanych) {
    ifstream zPliku{};
    int warstwy = 0;
    string nazwaPliku = "parametry.txt";
    zPliku.open(nazwaPliku);

    if(zPliku.good()) {
        string pomocniczy{};
         zPliku.ignore(100, ':');
         getline(zPliku, pomocniczy, ';');
         warstwy = stoi(pomocniczy);
         if(warstwy < 1 || warstwy > 5) {
             cout << "Liczba ukrytych warstw powinna sie miescic w przedziale <0,5>. Sprawdz poprawnosc danych w 2-giej linijce pliku txt.\n";
             zPliku.clear();
             zPliku.close();
             niepoprawnoscDanych = true;
             return 0;
         }
         cout << "Wczytana liczba ukrytych warstw neuronowych: " << warstwy << endl;
    }
         else {
             cout << "Niepoprawna sciezka do pliku z parametrami sieci!\n";
             zPliku.clear();
             zPliku.close();
             niepoprawnoscDanych = true;
             return 0;
         }
         return warstwy+1; // +1 bo wliczamy końcową warstwę
     }

double wczytywaniePoczatkowejWagi(bool& niepoprawnoscDanych) {
    ifstream zPliku{};
    double waga = 0;
    string nazwaPliku = "parametry.txt";
    zPliku.open(nazwaPliku);

    if(zPliku.good()) {
        string pomocniczy{};
         zPliku.ignore(100, ';');
         zPliku.ignore(100, ':');
         getline(zPliku, pomocniczy, ';');
         waga = stod(pomocniczy);
         if(waga <= 0 || waga > 1) {
             cout << "Waga operacji neuronow powinna sie miescic w przedziale (0,1>. Sprawdz poprawnosc danych w 3-ciej linijce pliku txt.\n";
             zPliku.clear();
             zPliku.close();
             niepoprawnoscDanych = true;
             return 0;
         }
         cout << "Wczytana waga poczatkowa dla wszystkich warstw: " << waga << endl;
    }
    else {
        cout << "Niepoprawna sciezka do pliku z parametrami sieci!\n";
        zPliku.clear();
        zPliku.close();
        niepoprawnoscDanych = true;
        return 0;
    }
    return waga;
}

double wczytywanieWspolczynnikaUczenia(bool& niepoprawnoscDanych) {
    ifstream zPliku{};
    double ucz = 0;
    string nazwaPliku = "parametry.txt";
    zPliku.open(nazwaPliku);

    if(zPliku.good()) {
        string pomocniczy{};
         zPliku.ignore(100, ';');
         zPliku.ignore(100, ';');
         zPliku.ignore(100, ':');
         getline(zPliku, pomocniczy, ';');
         ucz = stod(pomocniczy);
         if(ucz < 0.0001 || ucz > 1) {
             cout << "Wartosc wspolczynnika uczenia powinna miescic sie w przedziela <0.0001, 1> Sprawdz poprawnosc danych w 4-ej linijce pliku txt.\n";
             zPliku.clear();
             zPliku.close();
             niepoprawnoscDanych = true;
             return 0;
         }
         cout << "Wczytana wartosc wspolczynnika uczenia sie: " << ucz << endl << endl;


         zPliku.clear();
         zPliku.close();
     }
     else {
         cout << "Niepoprawna sciezka do pliku z parametrami sieci!\n";
         zPliku.clear();
         zPliku.close();
         niepoprawnoscDanych = true;
         return 0;
     }
    return ucz;
}

int wczytanieDanychIrysow(double**& irParam, int**& irSpec, string plik, bool& niepoprawnoscDanych) {           // wczesniej - wprowadzenieWektoraWejscia
    ifstream zPliku {};
    zPliku.open(plik);
    int licznikLiczb { 0 };
    double liczba { 0.0 };
    int rozmiarTablicy { 0 };

    if(!zPliku.good()) {
        cout << "Nieodnaleziono pliku o nazwie " << plik << endl;
        niepoprawnoscDanych = true;
        zPliku.clear();
        zPliku.close();
        return 0;
    }

    else {
        while(zPliku.good()) {
            zPliku >> liczba;
            if((liczba == 0 && licznikLiczb % 7 == 0) || (liczba == 1 && licznikLiczb % 7 == 0))
                break;
            licznikLiczb++;
        }
        zPliku.clear();
        zPliku.seekg(0, ios_base::beg);

        rozmiarTablicy = licznikLiczb / 7;

        irParam = new double*[rozmiarTablicy];
        for(int i = 0; i < rozmiarTablicy; i++)
            irParam[i] = new double[liczbaParametrowIrysa + 1];         // + 1, bo w wejsciu jest potrzebny bias

        irSpec = new int*[rozmiarTablicy];
        for(int i = 0; i < rozmiarTablicy; i++)
            irSpec[i] = new int[liczbaGatunkowIrysa];

        licznikLiczb = 0;

        int licznikRzedu { 0 };
        while(zPliku.good()) {
            zPliku >> liczba;
            if(liczba < 0 || liczba > 1) {
                cout << "Odnaleziona niepoprawna wartosc w pliku " << plik << endl;
                niepoprawnoscDanych = true;
                return 0;
            }
            else {
                if((liczba == 0 && licznikLiczb % 7 == 0) || (liczba == 1 && licznikLiczb % 7 == 0))          // if fullfilled then most probably it's eof flag (it mirrors last registered stream? maybe because of liczba type - double)
                    break;

                if(licznikLiczb % 7 < 4)
                    irParam[licznikRzedu][licznikLiczb % 7] = liczba;
                else {
                    if(licznikLiczb % 7 == 4)
                        irParam[licznikRzedu][licznikLiczb % 7] = 1.0;
                    irSpec[licznikRzedu][(licznikLiczb % 7) - 4] = liczba;
                }
                if(licznikLiczb % 7 == 6)
                    licznikRzedu++;
                licznikLiczb++;
            }
        }

        zPliku.clear();
        zPliku.close();

        cout << "Rozmiar tablicy: " << rozmiarTablicy << endl;

        return rozmiarTablicy;
    }
}
