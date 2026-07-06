#include <iostream>
#include <string>
#include "Archer.h"
#include "Magician.h"
#include "Thief.h"
#include "Warrior.h"

int main() {
    std::string name;
    int hp, mp, power, defence;
    std::cout << "===========================================\n"
              << "   [ Dungeon Escape Text RPG ]\n"
              << "===========================================\n"
              << "Enter your hero's name: ";
    std::cin >> name;

    do {
        std::cout << "\nEnter HP and MP (50 or more): ";
        std::cin >> hp >> mp;
        if (hp < 50 || mp < 50) std::cout << "HP or MP is too low. Try again.\n";
    } while (hp < 50 || mp < 50);

    do {
        std::cout << "Enter Power and Defence (20 or more): ";
        std::cin >> power >> defence;
        if (power < 20 || defence < 20) std::cout << "Power or Defence is too low. Try again.\n";
    } while (power < 20 || defence < 20);

    int jobChoice;
    do {
        std::cout << "\n< Job Selection >\n"
                  << name << ", choose your job!\n"
                  << "1. Warrior   2. Mage   3. Rogue   4. Archer\n"
                  << "Choose: ";
        std::cin >> jobChoice;
    } while (jobChoice < 1 || jobChoice > 4);

    Player* player = nullptr;
    switch (jobChoice) {
    case 1: player = new Warrior(name, hp, mp, power, defence); break;
    case 2: player = new Magician(name, hp, mp, power, defence); break;
    case 3: player = new Thief(name, hp, mp, power, defence); break;
    case 4: player = new Archer(name, hp, mp, power, defence); break;
    }

    const char* bonusStat[] = { "", "HP", "MP", "Attack", "Defense" };
    std::cout << "* You became a " << player->getJob() << "! ("
              << bonusStat[jobChoice] << " +30)\n";
    player->attack();
    player->printPlayerStatus();
    player->gainHpPotion(5);
    player->gainMpPotion(5);
    std::cout << "* You received 5 HP Potions and 5 MP Potions.\n"
              << "============================================\n"
              << "< Character Upgrade >\n"
              << "1. HP UP    2. MP UP    3. Power x2\n"
              << "4. Defence x2  5. Show Status  0. Start Game\n"
              << "============================================\n";

    bool isGameStart = false;
    while (!isGameStart) {
        int choice;
        std::cout << "Choose: ";
        std::cin >> choice;
        if (choice < 0 || choice > 5) {
            std::cout << "Invalid input.\n";
            continue;
        }
        switch (choice) {
        case 1: player->useHpPotion(); break;
        case 2: player->useMpPotion(); break;
        case 3: player->setPower(player->getPower() * 2); break;
        case 4: player->setDefence(player->getDefence() * 2); break;
        case 5: player->printPlayerStatus(); break;
        case 0: std::cout << "Game Start!\n"; isGameStart = true; break;
        }
    }

    delete player;
    player = nullptr;
    return 0;
}
