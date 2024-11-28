#ifndef P1_CPP_LAB_RANDOMFACULTYGENERATOR_HPP
#define P1_CPP_LAB_RANDOMFACULTYGENERATOR_HPP

#include <array>
#include <format>
#include <random>
#include <sstream>

inline constexpr std::array major{
    "Mechaniczny",
    "Elektryczny",
    "Elektroniki",
    "Inzynierii Materialowej",
    "Matematyki",
    "Inzynierii Produkcji",
    "Technologii Drewna"
};

inline constexpr std::array city{
    "Wroclawskiej",
    "Warszawskiej",
    "Gdanskiej",
    "Poznanskiej",
    "Rzeszowskiej"
};

inline auto getRandomFaculty() -> std::string {
    static auto prng = std::mt19937{std::random_device{}()};
    auto fnd = std::uniform_int_distribution<std::size_t>{0, major.size() - 1};
    auto lnd = std::uniform_int_distribution<std::size_t>{0, city.size() - 1};
    const auto i1 = major[fnd(prng)];
    const auto i2 = city[lnd(prng)];    
    
    std::ostringstream oss;
    oss << "Wydzial " << i1 << " Politechniki " << i2;
    return oss.str();
}

#endif //P1_CPP_LAB_RANDOMFACULTYGENERATOR_HPP