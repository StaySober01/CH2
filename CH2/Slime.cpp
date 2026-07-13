#include "Slime.h"
#include "player.h"
#include <iostream>

Slime::Slime()
    : Monster("Slime", 30, 20, 10, "Slime Jelly", 30, 30) {}

void Slime::attack(Player* player) const {
    std::cout << "Slime body-slams " << player->getName() << "!\n";
}
