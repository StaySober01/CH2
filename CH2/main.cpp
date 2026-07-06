#include <iostream>
#include <string>
#include "Player.h"

int main()
{
    std::string name;
    int hp;
    int mp;
    int attack;
    int defence;

    std::cout << "===========================================\n";
    std::cout << "   [ Dungeon Escape Text RPG ]\n";
    std::cout << "===========================================\n";

    std::cout << "Enter your hero's name: ";
    std::cin >> name;

    while (true) {
        std::cout << "\nEnter HP and MP: (more than 50) ";
        std::cin >> hp >> mp;

        if (hp >= 50 && mp >= 50) {
            break;
        }

        std::cout << "HP or MP is too low. Try again.\n";
    }

    while (true) {
        std::cout << "Enter Attack and Defense: (more than 20)";
        std::cin >> attack >> defence;

        if (attack >= 50 && defence >= 50) {
            break;
        }

        std::cout << "Attack or Defence is too low. Try again.\n";
    }

    Player player(name, hp, mp, attack, defence);

    player.printStats();

    return 0;
}