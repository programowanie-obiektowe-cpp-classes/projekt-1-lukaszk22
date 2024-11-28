#include "Firma.hpp"
#include "Pracownik.hpp"
#include "RandomNameGenerator.hpp"
#include "RandomFacultyGenerator.hpp"

int main()
{
    double kap_zakl = 50000.0;
    Firma firma(kap_zakl);

    std::string komenda;
    std::random_device rd;
    std::mt19937 gen(rd());

    double kwota;
    int czas_splaty;
    bool wynik =true;
    int upr;

    std::uniform_real_distribution<double> dist_but(36.0, 45.0);
    std::uniform_int_distribution<int> dist_obs(100, 50000);
    std::uniform_int_distribution<int> dist_upr(0, 1);
        
    upr = static_cast<bool>(dist_upr(gen));


    // Rozpoczecie gry z jednym pracownikiem kazdego typu
        firma.zatrudnijInz(getRandomName(), getRandomFaculty());
        firma.zatrudnijMag(getRandomName(), upr);
        firma.zatrudnijMkt(getRandomName(), dist_obs(gen));
        firma.zatrudnijRob(getRandomName(), dist_but(gen));

    std::cout << "Rozpoczynasz gre, wybierz dalsze kroki\n";

    while (true) {
        std::cout << "\nWybierz komende (lp, zinz, zmag, zmkt, zrob, kred, kt, help, exit):\n";
        std::cout << "W razie pomocy wpisz 'help':\n";
        std::cin >> komenda;
        upr = static_cast<bool>(dist_upr(gen));

        if (komenda == "lp") {
            firma.drukuj_pracownikow();
        } else if (komenda == "zinz") {
            firma.zatrudnijInz(getRandomName(), getRandomFaculty());
        } else if (komenda == "zmag") {
            firma.zatrudnijMag(getRandomName(), upr);
        } else if (komenda == "zmkt") {
            firma.zatrudnijMkt(getRandomName(), dist_obs(gen));
        } else if (komenda == "zrob") {
            firma.zatrudnijRob(getRandomName(), dist_but(gen));
        } else if (komenda == "kred") {
            std::cout << "Podaj kwote kredytu :";
            std::cin >> kwota;
            std::cout << "Podaj czas splaty :";
            std::cin >>czas_splaty;
            firma.wezKredyt(kwota, czas_splaty);
        } else if (komenda == "kt") {
            wynik = firma.zakonczTure();
            if(wynik==false){
                break;
            }
        } else if (komenda == "exit") {
            break;
        } else if (komenda == "help") {
            firma.help();
        } else {
            std::cout << "Nieznana komenda, sprobuj jeszcze raz\n";
        }
    }

    std::cout << "Koniec gry, do zobaczenia!\n";
    return 0;
}
