#include "Dragon.h"
#include "player.h"
#include <iostream>

Dragon::Dragon()
    : Monster("Dragon", 120, 42, 20, "Dragon Scale", 300, 150) {}

void Dragon::attack(Player* player) const {
    std::cout << "Dragon breathes fire at " << player->getName() << "!\n";
}
