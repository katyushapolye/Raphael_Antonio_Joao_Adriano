#include "headers/Tile.hpp"

Tile::Tile()
{
    std::cout << "It's working as intended" << std::endl;
    f1();
}

void Tile::f1()
{
    std::cout << "Separated definition working too." << std::endl;
}
