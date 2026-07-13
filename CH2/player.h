#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include "Item.h"

class Monster;

class Player {
protected:
    std::string name;
    std::string job;
    int level;
    int exp;
    int maxExp;
    int hp;
    int mp;
    int maxHp;
    int maxMp;
    int power;
    int defence;
    int curHpPotion;
    int curMpPotion;
    std::vector<Item> inventory;

public:
    static constexpr std::size_t MAX_INVENTORY_SIZE = 10;

    Player(const std::string& name, int hp, int mp, int power, int defence);
    virtual ~Player() {}

    const std::string& getName() const;
    const std::string& getJob() const;
    int getLevel() const;
    int getExp() const;
    int getMaxExp() const;
    int getHp() const;
    int getHP() const;
    int getMp() const;
    int getMP() const;
    int getMaxHP() const;
    int getMaxMP() const;
    int getPower() const;
    int getDefence() const;
    void setName(const std::string& value);
    void setJob(const std::string& value);
    void setLevel(int value);
    void setHp(int value);
    void setHP(int value);
    void setMp(int value);
    void setMP(int value);
    void setPower(int value);
    void setDefence(int value);

    void printPlayerStatus() const;
    void takeDamage(int damage);
    void consumeMp(int amount);
    void gainExp(int amount);
    void gainHpPotion(int amount);
    void gainMpPotion(int amount);
    void useHpPotion();
    void useMpPotion();
    bool addItem(const Item& item);
    bool removeItem(std::size_t index);
    const std::vector<Item>& getInventory() const;
    virtual void attack(Monster* monster) = 0;
};
