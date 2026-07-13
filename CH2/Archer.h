#pragma once
#include "player.h"
class Archer : public Player {
public:
    Archer(const std::string& name, int hp, int mp, int power, int defence);
    void attack(Monster* monster) override;
};
