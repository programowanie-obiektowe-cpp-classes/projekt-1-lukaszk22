#include "../include/Pracownik.hpp"

// ---------------------------------------------------------------------------------------------
// Metody klasy Pracownik
Pracownik::Pracownik(const std::string& imie) : imie_{imie}
{
}

void Pracownik::print(){
    std::cout << "Imie pracownika: " << imie_ << std::endl;
}

// ---------------------------------------------------------------------------------------------
// Metody klasy Inżynier
Inzynier::Inzynier(std::string imie, std::string wydzial) : Pracownik(imie), Inż_{wydzial}
{
}

void Inzynier::print(){
    std::cout << "Imie inzyniera: " << imie_ << std::endl;
    std::cout << "Ukonczony wydzial: " << Inż_<< std::endl;
}

// ---------------------------------------------------------------------------------------------
// Metody klasy Magazynier
Magazynier::Magazynier(std::string imie, bool uprawnienia) : Pracownik(imie), Mag_{uprawnienia}
{
}

void Magazynier::print(){
    std::cout << "Imie magazyniera: " << imie_ << std::endl;
    std::cout << "Uprawnienia do kierowania wozkiem widlowym: ";
    if(Mag_ == true){
        std::cout << "posiada. " << std::endl;
    }
    else{
        std::cout << "nie posiada. " << std::endl;
    }
}

// ---------------------------------------------------------------------------------------------
// Metody klasy Marketer
Marketer::Marketer(std::string imie, int lObs) : Pracownik(imie), Mkt_(lObs)
{
}

void Marketer::print(){
    std::cout << "Imie marketera: " << imie_ << std::endl;
    std::cout << "Liczba obserwujacych: " << Mkt_ << std::endl;
}

// ---------------------------------------------------------------------------------------------
// Metody klasy Robotnik
Robotnik::Robotnik(std::string imie, double stopa) : Pracownik(imie), Rob_(stopa)
{
}

void Robotnik::print(){
    std::cout << "Imie robotnika: " << imie_ << std::endl;
    std::cout << "Rozmiar buta: " << Rob_ << std::endl;
}
