#include "Skeleton.h"
#include "player.h"
#include <iostream>

Skeleton::Skeleton()
    : Monster("Skeleton", 45, 35, 12, "Bone Fragment", 60, 50) {}

void Skeleton::attack(Player* player) const {
    std::cout << "Skeleton slashes " << player->getName() << " with a rusty sword!\n";
}
