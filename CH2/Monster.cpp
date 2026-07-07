#include "Monster.h"
#include "player.h"
#include <iostream>

Monster::Monster(const std::string& name, int hp, int power, int defence,
                 const std::string& dropItemName, int dropItemPrice)
    : name(name), hp(hp), power(power), defence(defence),
      dropItemName(dropItemName), dropItemPrice(dropItemPrice) {}

const std::string& Monster::getName() const { return name; }
int Monster::getHP() const { return hp; }
int Monster::getPower() const { return power; }
int Monster::getDefence() const { return defence; }
const std::string& Monster::getDropItemName() const { return dropItemName; }
int Monster::getDropItemPrice() const { return dropItemPrice; }

void Monster::setHP(int value) { hp = value; }

void Monster::attack(Player* player) const {
    std::cout << name << " attacks " << player->getName() << "!\n";
}
