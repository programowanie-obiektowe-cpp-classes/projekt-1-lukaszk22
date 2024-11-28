#ifndef PRACOWNIK_HPP
#define PRACOWNIK_HPP

#include <string>
#include <iostream>

// Definicja klasy bazowej Pracownik
class Pracownik
{
protected:
    std::string imie_;
public:
    Pracownik(const std::string& imie);
    virtual ~Pracownik() = default;

    Pracownik(const Pracownik& p) = default;
    Pracownik& operator=(const Pracownik& p) = default;

    virtual void print();
};

// Definicja klasy Inżynier
class Inzynier : public Pracownik
{
private:
    double CI_;
    std::string Inż_;        // Nazwa skończonego wydziału

    unsigned int N_inz_;     // numer inżyniera
public:
    Inzynier(std::string imie, std::string wydzial);

    void print () override;
};


// Definicja klasy Magazynier
class Magazynier : public Pracownik
{
private:
    double CMag_;
    bool Mag_;               // Wskaźnik czy posiada uprawnienia do prowadzenia wózka

    unsigned int N_mag_;     // numer magazyniera
public:
    Magazynier(std::string imie, bool uprawnienia);

    void print () override;
};


// Definicja klasy Marketer
class Marketer : public Pracownik
{
private:
    double CMkt_;
    int Mkt_;                // Liczba obserwujących w mediach społecznościowych

    unsigned int N_mkt_;     // numer marketera
public:
    Marketer(std::string imie, int lObs);

    void print () override;
};


// Definicja klasy Robotnik
class Robotnik : public Pracownik
{
private:
    double CRob_;
    double Rob_;             // Rozmar stopy robotnika

    unsigned int N_rob_;     // numer robotnika
public:
    Robotnik(std::string imie, double stopa);

    void print () override;
};

#endif // PRACOWNIK_HPP