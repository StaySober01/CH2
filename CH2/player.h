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

    void setHP(int damage) {
        stat.HP -= damage;
    }

    void setMP(int consumedMp) {
        stat.MP -= consumedMp;
    }
};