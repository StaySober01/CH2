#pragma once

#include "Monster.h"

class Zombie : public Monster {
public:
    Zombie();
    void attack(Player* player) const override;
};
