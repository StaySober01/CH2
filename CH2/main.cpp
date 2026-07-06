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

    std::cout << "\nEnter HP and MP: ";
    std::cin >> hp >> mp;

    std::cout << "Enter Attack and Defense: ";
    std::cin >> attack >> defence;

    Player player(name, hp, mp, attack, defence);

    player.printStats();

    return 0;
}