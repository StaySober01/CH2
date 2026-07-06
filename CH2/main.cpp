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
    bool isGameStart = false;

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

        if (attack >= 20 && defence >= 20) {
            break;
        }

        std::cout << "Attack or Defence is too low. Try again.\n";
    }

    Player player(name, hp, mp, attack, defence);

    player.printStats();
    player.GainHpPotion(5);
    player.GainMpPotion(5);

    std::cout << "* You received 5 HP Potions and 5 MP Potions.\n";
    std::cout << "============================================\n";
    std::cout << "< Character Upgrade >\n";
    std::cout << "1. HP UP    2. MP UP    3. Attack x2\n";
    std::cout << "4. Defense x2  5. Show Stats  0. Start Game\n";
    std::cout << "============================================\n";

    while (!isGameStart) {
        int choose;
        std::cout << "Choose : ";
        std::cin >> choose;
        if (choose < 0 && choose > 5) {
            std::cout << "invalid input\n";
            continue;
        }

        Stat curStat = player.GetStat();

        switch (choose)
        {
        case 1:
            player.UseHpPotion();
            break;

        case 2:
            player.UseMpPotion();
            break;

        case 3:
            player.SetAttack(curStat.Attack * 2);
            break;

        case 4:
            player.SetDefence(curStat.Defence * 2);
            break;

        case 5:
            player.printStats();
            break;

        case 0:
            std::cout << "Game Start!\n";
            isGameStart = true;
            break;

        default:
            break;
        }
    }

    return 0;
}