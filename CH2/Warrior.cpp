#include "Warrior.h"
#include <iostream>
Warrior::Warrior(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) { job = "Warrior"; this->hp += 30; }
void Warrior::attack() { std::cout << "* Swings a mighty sword!\n"; }
