#pragma once
#include <string>
#include <iostream>

struct Stat {
    int HP;
    int MP;
    int Attack;
    int Defence;
};

class Player {
private:
    std::string name;
    Stat stat;
    int curHpPotion = 0;
    int curMpPotion = 0;

protected:
    

public:
    Player(const std::string& name, int hp, int mp, int attack, int defence)
        : name(name), stat{ hp, mp, attack, defence }
    {
    }

    void printStats() const {
        std::cout << "\n====================================\n";
        std::cout << "  " << name << "'s Stats\n";
        std::cout << "====================================\n";
        std::cout << "HP: " << stat.HP << "    MP: " << stat.MP << '\n';
        std::cout << "Attack: " << stat.Attack << "    Defense: " << stat.Defence << '\n';
        std::cout << "====================================\n";
    }

    void AnyDamage(int damage) {
        stat.HP -= damage;
    }

    void ConsumeMP(int consumedMp) {
        stat.MP -= consumedMp;
    }

    void SetHP(int hp) {
        stat.HP = hp;
    }

    void SetMP(int mp) {
        stat.MP = mp;
    }

    void SetAttack(int attack) {
        stat.Attack = attack;
    }

    void SetDefence(int defence) {
        stat.Defence = defence;
    }

    Stat GetStat() {
        return stat;
    }

    void GainHpPotion(int amount) {
        curHpPotion += amount;
    }

    void GainMpPotion(int amount) {
        curMpPotion += amount;
    }

    void UseHpPotion() {
        if (curHpPotion <= 0) {
            std::cout << "You don't have Hp potion.\n";
            return;
        }
        stat.HP += 20;
        curHpPotion--;
        std::cout << "You've got 20 Hp.(Current Hp Potion: " << curHpPotion << ")\n";
    }

    void UseMpPotion() {
        if (curMpPotion <= 0) {
            std::cout << "You don't have Mp potion.\n";
            return;
        }
        stat.MP += 20;
        curMpPotion--;
        std::cout << "You've got 20 Mp.(Current Mp Potion: " << curMpPotion << ")\n";
    }
};