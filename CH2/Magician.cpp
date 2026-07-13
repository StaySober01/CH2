#include "Magician.h"
#include "Monster.h"
#include <iostream>
Magician::Magician(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "Mage";
    this->mp += 30;
    this->maxMp += 30;
}
void Magician::attack(Monster* monster) {
    int damage = power - monster->getDefence();
    if (damage <= 0) damage = 1;

    monster->setHP(monster->getHP() - damage);
    std::cout << "[Mage] Fires fireball! -> " << damage
              << " damage to " << monster->getName() << "!\n";
}
