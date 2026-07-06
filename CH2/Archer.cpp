#include "Archer.h"
#include <iostream>
Archer::Archer(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) { job = "Archer"; this->defence += 30; }
void Archer::attack() { std::cout << "* Fires a precise arrow!\n"; }
