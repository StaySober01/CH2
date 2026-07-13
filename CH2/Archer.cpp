#include "Archer.h"
#include "Monster.h"
#include <iostream>
Archer::Archer(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) { job = "Archer"; this->defence += 30; }
void Archer::attack(Monster* monster) {
    int damage = power / 3 - monster->getDefence();
    if (damage <= 0) damage = 1;

    for (int hit = 0; hit < 3; ++hit) {
        monster->setHP(monster->getHP() - damage);
    }

    std::cout << "[Archer] Shoots arrow! -> " << damage
              << " damage to " << monster->getName() << "! (x3)\n";
}
