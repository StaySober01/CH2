#pragma once
#include "player.h"
class Thief : public Player {
public:
    Thief(const std::string& name, int hp, int mp, int power, int defence);
    void attack() override;
};
