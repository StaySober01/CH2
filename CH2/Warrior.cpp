#include "Warrior.h"
#include "Monster.h"
#include <iostream>
Warrior::Warrior(const std::string& name, int hp, int mp, int power, int defence)
    : Player(name, hp, mp, power, defence) {
    job = "Warrior";
    this->hp += 30;
    this->maxHp += 30;
}
void Warrior::attack(Monster* monster) {
    int damage = power - monster->getDefence();
    if (damage <= 0) damage = 1;

    monster->setHP(monster->getHP() - damage);
    std::cout << "[Warrior] Swings sword! -> " << damage
              << " damage to " << monster->getName() << "!\n";
}
