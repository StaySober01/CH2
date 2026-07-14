#pragma once

#include "Monster.h"

class Dragon : public Monster {
public:
    Dragon();
    void attack(Player* player) const override;
};
