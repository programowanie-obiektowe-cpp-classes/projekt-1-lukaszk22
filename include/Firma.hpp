#include <iostream>
#include <vector>
#include <array>
#include <numeric>
#include <random>
#include <algorithm>
#include "Pracownik.hpp"

class Firma
{
private:
    
    double budzet_;
    int miesiac_;

    bool stan = true;
    // Stale modelu
    const int CMag_ = 7;
    const double CI_ = 1500.;
    const int CMkt_ = 8;
    const int CRob_ = 5;
    int N_ = 10;
    int M_ = 3;

    // Zarobki
    const double wynInz = 8000;
    const double wynMkt = 7000;
    const double wynMag = 6000;
    const double wynRob = 5000;

    // Liczba pracownikow
    unsigned int N_inz      = 0;
    unsigned int N_mag      = 0;
    unsigned int N_mkt      = 0;
    unsigned int N_rob      = 0;

    int pojemnosc           = 0;
    double cena             = 0;
    int popyt               = 0;
    int lProd               = 0;
    int lProd_sprzed        = 0;
    int lProd_wyp           = 0;
    double przychod         = 0;
    double rynek            = 0;
    int stan_na_magazynie   = 0;

    double wartosc_         = 0.;
    double dochod_          = 0.;

    unsigned int czas_splaty_max    = 12;
    double rata                     = 0.;
    unsigned int l_rat              = 0;

    double stan_konta_              = 0.;
    int n_kredytow_                 = 0;
    std::vector<double> historia_przych_;
    std::vector<std::unique_ptr<Pracownik>> pracownicy;

public:

// Konstruktor domyślny
    Firma(double budzet_0) : budzet_(budzet_0), miesiac_(1) {
    }

//
 void zatrudnijInz(const std::string& imie, const std::string& wydzial);

 void zatrudnijMag(const std::string& imie, const bool& uprawnienia);

 void zatrudnijMkt(const std::string& imie, const int& lObs);

 void zatrudnijRob(const std::string& imie, const double& stopa);

 void help();

 bool zakonczTure();

 void wezKredyt(double kwota, unsigned int czas_splaty);

void drukuj_pracownikow();

};



