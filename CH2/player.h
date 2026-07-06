#pragma once
#include <string>

class Player {
protected:
    std::string name;
    std::string job;
    int level;
    int hp;
    int mp;
    int power;
    int defence;
    int curHpPotion;
    int curMpPotion;

public:
    Player(const std::string& name, int hp, int mp, int power, int defence);
    virtual ~Player() {}

    const std::string& getName() const;
    const std::string& getJob() const;
    int getLevel() const;
    int getHp() const;
    int getMp() const;
    int getPower() const;
    int getDefence() const;
    void setName(const std::string& value);
    void setJob(const std::string& value);
    void setLevel(int value);
    void setHp(int value);
    void setMp(int value);
    void setPower(int value);
    void setDefence(int value);

    void printPlayerStatus() const;
    void takeDamage(int damage);
    void consumeMp(int amount);
    void gainHpPotion(int amount);
    void gainMpPotion(int amount);
    void useHpPotion();
    void useMpPotion();
    virtual void attack() = 0;
};
