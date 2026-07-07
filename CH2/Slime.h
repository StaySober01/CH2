#pragma once

#include "Monster.h"

class Slime : public Monster {
public:
    Slime();
    void attack(Player* player) const override;
};
