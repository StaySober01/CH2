#pragma once

#include "Monster.h"

class Skeleton : public Monster {
public:
    Skeleton();
    void attack(Player* player) const override;
};
