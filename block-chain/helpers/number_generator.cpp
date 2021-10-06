#include "number_generator.hpp"

//konstruktorius
RandomInt::RandomInt() : mt{rd()} {}

//skaičiaus generavimas
int RandomInt::rnd(int low, int high) {
    std::uniform_int_distribution<int> dist(low, high);
    return dist(mt);
}