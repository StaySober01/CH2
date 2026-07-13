#pragma once

#include <string>

class Player;

class Monster {
private:
    std::string name;
    int hp;
    int power;
    int defence;
    std::string dropItemName;
    int dropItemPrice;
    int expReward;

public:
    Monster(const std::string& name, int hp, int power, int defence,
            const std::string& dropItemName, int dropItemPrice, int expReward);
    virtual ~Monster() = default;

    const std::string& getName() const;
    int getHP() const;
    int getPower() const;
    int getDefence() const;
    const std::string& getDropItemName() const;
    int getDropItemPrice() const;
    int getExpReward() const;

    void setHP(int value);
    virtual void attack(Player* player) const;
};
