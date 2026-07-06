#include "Thief.h"
#include <iostream>
Thief::Thief(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) { job = "Rogue"; this->power += 30; }
void Thief::attack() { std::cout << "* Strikes swiftly with twin daggers!\n"; }
