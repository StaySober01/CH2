#pragma once
#include "player.h"
class Magician : public Player {
public:
    Magician(const std::string& name, int hp, int mp, int power, int defence);
    void attack(Monster* monster) override;
};
