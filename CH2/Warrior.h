#pragma once
#include "player.h"
class Warrior : public Player {
public:
    Warrior(const std::string& name, int hp, int mp, int power, int defence);
    void attack() override;
};
