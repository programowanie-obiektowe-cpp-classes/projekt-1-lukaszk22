#include "../include/Firma.hpp"
#include "../include/Pracownik.hpp"

void Firma::drukuj_pracownikow(){

    std::cout << "\nLISTA PRACOWNIKOW (stan na miesiac nr. " << miesiac_ << " ):\n\n";;
    std::cout << "Inzynierowie (" << N_inz << "):\n";
    for (const auto& prac : pracownicy) {
        if (dynamic_cast<Inzynier*>(prac.get())) {
            prac->print();
        }
    }
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "Magazynierzy (" << N_mag << "):\n";
    for (const auto& prac : pracownicy) {
        if (dynamic_cast<Magazynier*>(prac.get())) {
            prac->print();
        }
    }
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "Marketerzy (" << N_mkt << "):\n";
    for (const auto& prac : pracownicy) {
        if (dynamic_cast<Marketer*>(prac.get())) {
            prac->print();
        }
    }
    std::cout << "---------------------------------------------------------------------\n";
    std::cout << "Robotnicy (" << N_rob << "):\n";
    for (const auto& prac : pracownicy) {
        if (dynamic_cast<Robotnik*>(prac.get())) {
            prac->print();
        }
    }
    std::cout << "---------------------------------------------------------------------\n\n";
}

void Firma::wezKredyt(double kwota, unsigned int czas_splaty){

    if(czas_splaty>czas_splaty_max){
        std::cout << "Nie mozesz wziac kredytu na tak dlugo, maksymalny czas to 12 miesiecy \n";
    }
    else if(czas_splaty < 1){
        std::cout << "Za krotki czas splaty kredytu\n";
    }
    else if(l_rat>0){
        std::cout << "Juz masz wazny kredyt, nie mozesz wziac kolejnego\n" << std::endl;
    }
    else if(wartosc_*static_cast<double>(M_) < kwota){
        std::cout << "Nie mozesz wziac kredytu na zaproponowana sume" << std::endl;
        std::cout << "Przy wartosci firmy na poziomie: " << wartosc_ << " PLN, maksymalna kwota kredytu to: " << wartosc_*static_cast<double>(M_) << " PLN\n" << std::endl;
    }
    else{
        l_rat = czas_splaty;
        std::cout << "Bank umozliwia Ci wziecie kredytu" << std::endl;
        std::cout << "Dla kredytu na czas: " << czas_splaty << " proponowane oprocentowanie to " << 5.*static_cast<double>(czas_splaty) << "% w skali roku" << std::endl;

        budzet_+=kwota;
        if(l_rat >0){
        rata = kwota/static_cast<double>(czas_splaty) * (1+0.05*static_cast<double>(czas_splaty));
        }
        else{
        rata = 0;
        }

        std::cout << "Twoja rata miesieczna wynosi: " << rata << " PLN" << std::endl;
        std::cout << "Twoj budzet to aktualnie: " << budzet_ << " PLN" << std::endl;
    }
}

bool Firma::zakonczTure(){
    std::cout << "\n------------------------------------------------------------------------------------\n";
    std::cout << "Miesiac nr. " << miesiac_ << " sie zakonczyl\n";
    ++miesiac_;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist_popyt(0, 5);
    std::uniform_int_distribution<int> dist_awaria(1, 100);
    std::uniform_int_distribution<int> dist_kryzys(1, 100);
    std::uniform_int_distribution<int> dist_kradziez(0, 100);

    // Wyznaczenie mozliwosci przerobowych
    pojemnosc = CMag_*N_mag;
    cena = CI_*static_cast<double>(N_inz);

    if(dist_kryzys(gen)<5){
        cena = cena*0.5;
        std::cout << "!!!" << std::endl;
        std::cout << "UWAGA: Wszechobecny kryzys spowodowal gwaltowny spadek ceny twojego produktu." << std::endl;
        std::cout << "!!!" << std::endl;
    }

    // Produkcja
    lProd_wyp = static_cast<int>(CRob_*N_rob);

    if(dist_awaria(gen)<10){
        std::cout << "!!!" << std::endl;
        std::cout << "UWAGA: Nastapila awaria linii produkcyjnej! Nie udalo ci sie wyprodukowac zadnego produktu w tym miesiacu." << std::endl;
        std::cout << "!!!" << std::endl;
        lProd_wyp = 0;
    }

    lProd = lProd_wyp+stan_na_magazynie;
    lProd = std::min(lProd, pojemnosc);

    // Ocena mozliwosci sprzedazowych
    popyt = CMkt_*N_mkt*static_cast<int>(dist_popyt(gen));
    lProd_sprzed = std::min(popyt, lProd);

    if(popyt == 0){
        std::cout << "!!!" << std::endl;
        std::cout << "UWAGA: Wyniki sprzedazowe w tym miesiacu sa bardzo slabe. Nie udalo Ci sie sprzedac zadnego produktu." << std::endl;
        std::cout << "!!!" << std::endl;
    }

    // Okreslenie stanu na magazynie po sprzedazy
    stan_na_magazynie = lProd-lProd_sprzed;
    stan_na_magazynie = std::min(stan_na_magazynie, pojemnosc);
    if(dist_kradziez(gen)<20 && stan_na_magazynie>0){
        stan_na_magazynie = 0;
        std::cout << "!!!" << std::endl;
        std::cout << "UWAGA: Zostales okradziony! Straciles towar ktory zostal w magazynie po sprzedazy!" << std::endl;
        std::cout << "!!!" << std::endl;
    }

    // Ocena przychodu i wartosci spolki
    przychod = cena*lProd_sprzed;
    historia_przych_.push_back(przychod);

    if(historia_przych_.size()<N_){
        wartosc_ = std::accumulate(historia_przych_.begin(), historia_przych_.end(), 0.0)/static_cast<double>(historia_przych_.size());
    }
    else
    {
    wartosc_ = std::accumulate(historia_przych_.end() - N_, historia_przych_.end(), 0.0)/static_cast<double>(N_);
    }

    // Okreslenie wynagrodzenia pracownikow
    double wynPrac = static_cast<double>(N_inz)*wynInz + static_cast<double>(N_mag)*wynMag + static_cast<double>(N_mkt)*wynMkt + static_cast<double>(N_rob)*wynRob;

    // Okreslenie dochodu firmy
    dochod_ = przychod - wynPrac - rata;
    // Okreslenie budzetu
    budzet_+= dochod_;
    if(l_rat>0){
    --l_rat;
    }
    
    std::cout << "Pojemnosc magazynu dla " << N_mag << " magazynierow wynosi: " << pojemnosc << std::endl;
    std::cout << "Cena produktu dla  " << N_inz << " inzynierow wynosi: " << cena << " PLN" <<std::endl;
    std::cout << "Zatrudniajac " << N_rob << " robotnikow miesiacu dysponowano: " << lProd << " produktami" << std::endl;
    std::cout << "Zatrudniajac " << N_mkt << " marketerow sprzedano: " << lProd_sprzed << " produktow" << std::endl;
    std::cout << "Na stanie w magazynie zostalo " << stan_na_magazynie << " produktow\n" << std::endl;

    std::cout << "RAPORT:\n" << std::endl;
    
    std::cout << "Przychod: \t\t\t\t" << przychod << "\tPLN" <<std::endl;
    std::cout << "Wynagrodzenie pracownikow: \t\t" << wynPrac << "\tPLN" <<std::endl;
    std::cout << "Rata kredytu: \t\t\t\t" << rata << "\tPLN" <<std::endl;
    std::cout << "Liczba nastepnych rat do splacenia: \t" << l_rat << "\t[-]" <<std::endl;

    std::cout << "Wartosc spolki: \t\t\t" << wartosc_ << "\tPLN" << std::endl;
    std::cout << "Dochod spolki: \t\t\t\t" << dochod_ << "\tPLN" <<std::endl;
    std::cout << "Budzet spolki: \t\t\t\t"  << budzet_ << "\tPLN" <<std::endl;

    if(budzet_ <0){
        std::cout << "Zbankrutowales, musisz oglosic upadlosc." << std::endl;
        stan = false;
    }
    if(budzet_ >1e6){
        std::cout << "Gratulacje, twoj budzet wynosi milion! Wygrales gre!" << std::endl;
        stan = false;
    }

    return stan;
    
}

void Firma::zatrudnijInz(const std::string& imie, const std::string& wydzial) {
        pracownicy.push_back(std::make_unique<Inzynier>(imie, wydzial));
        ++N_inz;
    }

 void Firma::zatrudnijMag(const std::string& imie, const bool& uprawnienia){
        pracownicy.push_back(std::make_unique<Magazynier>(imie, uprawnienia));
        ++N_mag;
 }

 void Firma::zatrudnijMkt(const std::string& imie, const int& lObs){
        pracownicy.push_back(std::make_unique<Marketer>(imie, lObs));
        ++N_mkt;
 }

 void Firma::zatrudnijRob(const std::string& imie, const double& stopa){
        pracownicy.push_back(std::make_unique<Robotnik>(imie, stopa));
        ++N_rob;
 }

 void Firma::help(){
    std::cout << "------------------------------------------------------------------" << std::endl;
            std::cout << "INSTRUKCJA GRY" << std::endl;
            std::cout << "------------------------------------------------------------------" << std::endl;
            std::cout << "Gra polega na zarzadzaniu firma. Celem jest osiagniecie budzetu w firmie na poziomie 1 miliona PLN." << std::endl;
            std::cout << "Gra sie poprzez zarzadzanie kadra pracownicza. Zatrudniajac poszczegolnych pracownikow mozesz wplywac na: " << std::endl;
            std::cout << "-> rozmiar magazynu" << std::endl;
            std::cout << "-> cene produktu" << std::endl;
            std::cout << "-> ilosc produktu produkowana w miesiacu" << std::endl;
            std::cout << "-> promocje produktu i sprzedaz" << std::endl;
            std::cout << "Gre zaczynasz z 50 000 PLN na koncie\n" << std::endl;
            std::cout << "------------------------------------------------------------------" << std::endl;
            std::cout << "-KOMENDY" << std::endl;
            std::cout << "------------------------------------------------------------------" << std::endl;
            std::cout << "-> lp - wyswietla liste pracownikow" << std::endl;
            std::cout << "-> zinz - zatrudnia inzyniera" << std::endl;
            std::cout << "\t - zwiekszenie liczby inzynierow zwieksza cene produktu, utrzymanie inzyniera kosztuje 8000 PLN miesiecznie" << std::endl;
            std::cout << "-> zmag - zatrudnia magazyniera" << std::endl;
            std::cout << "\t - zwiekszenie liczby magazynierow zwieksza pojemnosc magazynu, utrzymanie magazyniera kosztuje 6000 PLN miesiecznie" << std::endl;
            std::cout << "-> zmkt - zatrudnia marketera" << std::endl;
            std::cout << "\t - zwiekszenie liczby marketerow poprawia sprzedaz, utrzymanie marketera kosztuje 7000 PLN miesiecznie" << std::endl;
            std::cout << "-> zrob - zatrudnia robotnika" << std::endl;
            std::cout << "\t - zwiekszenie liczby robotnikow zwieksza produkcje, utrzymanie robotnika kosztuje 5000 PLN miesiecznie" << std::endl;
            std::cout << "-> kred - umozliwia wziecie kredytu" << std::endl;
            std::cout << "\t - kredyt maksymalnie moze byc splacany 12 miesiecy" << std::endl;
            std::cout << "\t - oprocentowanie kredytu rosie wraz z czasem splacania" << std::endl;
            std::cout << "\t - maksymalna kwota kredytu zalezy od wartosci spolki" << std::endl;
            std::cout << "-> exit - wychodzi z gry\n" << std::endl;

            std::cout << "Uwazaj! Gra sie konczy gdy twoj budzet spadnie ponizej 0 PLN" << std::endl;
 }