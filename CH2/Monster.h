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

public:
    Monster(const std::string& name, int hp, int power, int defence,
            const std::string& dropItemName, int dropItemPrice);
    virtual ~Monster() = default;

    const std::string& getName() const;
    int getHP() const;
    int getPower() const;
    int getDefence() const;
    const std::string& getDropItemName() const;
    int getDropItemPrice() const;

    void setHP(int value);
    virtual void attack(Player* player) const;
};
