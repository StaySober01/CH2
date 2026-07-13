#include "Thief.h"
#include "Monster.h"
#include <iostream>
Thief::Thief(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) { job = "Rogue"; this->power += 30; }
void Thief::attack(Monster* monster) {
    int damage = power / 5 - monster->getDefence();
    if (damage <= 0) damage = 1;

    for (int hit = 0; hit < 5; ++hit) {
        monster->setHP(monster->getHP() - damage);
    }

    std::cout << "[Rogue] Stabs dagger! -> " << damage
              << " damage to " << monster->getName() << "! (x5)\n";
}
