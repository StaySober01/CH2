#include "Zombie.h"
#include "player.h"
#include <iostream>

Zombie::Zombie()
    : Monster("Zombie", 60, 28, 15, "Rotten Tooth", 50) {}

void Zombie::attack(Player* player) const {
    std::cout << "Zombie bites " << player->getName() << "!\n";
}
