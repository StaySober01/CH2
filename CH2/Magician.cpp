#include "Magician.h"
#include <iostream>
Magician::Magician(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) { job = "Mage"; this->mp += 30; }
void Magician::attack() { std::cout << "* Fires a fireball!\n"; }
