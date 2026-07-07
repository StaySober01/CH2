#include <array>
#include <iostream>
#include <limits>
#include <string>
#include "Archer.h"
#include "Magician.h"
#include "Monster.h"
#include "Thief.h"
#include "Warrior.h"

int calculateDamage(int power, int defence) {
    int damage = power - defence;
    return damage > 0 ? damage : 1;
}

void battle(Player* player, Monster& monster) {
    std::cout << "\n[ Battle Start! ] " << player->getName() << '(' << player->getJob()
              << ") vs " << monster.getName() << "\n";

    while (player->getHP() > 0 && monster.getHP() > 0) {
        std::cout << "\n--- Player Turn ---\n";
        player->attack();

        int damage = calculateDamage(player->getPower(), monster.getDefence());
        int beforeHP = monster.getHP();
        monster.setHP(beforeHP - damage);
        std::cout << damage << " damage to " << monster.getName() << "!\n"
                  << monster.getName() << " HP: " << beforeHP << " -> " << monster.getHP();
        if (monster.getHP() <= 0) std::cout << " (Dead)";
        std::cout << '\n';

        if (monster.getHP() <= 0) break;

        std::cout << "\n--- Monster Turn ---\n";
        monster.attack(player);

        damage = calculateDamage(monster.getPower(), player->getDefence());
        beforeHP = player->getHP();
        player->setHP(beforeHP - damage);
        std::cout << damage << " damage to " << player->getName() << "!\n"
                  << player->getName() << " HP: " << beforeHP << " -> " << player->getHP();
        if (player->getHP() <= 0) std::cout << " (Dead)";
        std::cout << '\n';
    }

    if (monster.getHP() <= 0) {
        std::cout << "\n[==Victory!==]\n"
                  << "  -> Got: " << monster.getDropItemName() << "!\n"
                  << "  (Will be saved to inventory in the next STEP)\n";
    }
    else {
        std::cout << "\nDefeat... " << player->getName() << " has fallen.\n";
    }
}

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

    int jobChoice = 0;
    while (true) {
        std::cout << "\n< Job Selection >\n"
                  << name << ", choose your job!\n"
                  << "1. Warrior   2. Mage   3. Rogue   4. Archer\n"
                  << "Choose: ";

        if (std::cin >> jobChoice && jobChoice >= 1 && jobChoice <= 4) {
            break;
        }

        std::cout << "Invalid input. Enter a number from 1 to 4.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Player* player = nullptr;
    switch (jobChoice) {
    case 1: player = new Warrior(name, hp, mp, power, defence); break;
    case 2: player = new Magician(name, hp, mp, power, defence); break;
    case 3: player = new Thief(name, hp, mp, power, defence); break;
    case 4: player = new Archer(name, hp, mp, power, defence); break;
    default:
        std::cerr << "Failed to create player.\n";
        return 1;
    }

    const std::array<const char*, 5> bonusStat = { "", "HP", "MP", "Attack", "Defense" };
    std::cout << "* You became a " << player->getJob() << "! ("
              << bonusStat.at(static_cast<std::size_t>(jobChoice)) << " +30)\n";
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

    Monster slime("Slime", 30, 20, 10, "Slime Jelly", 10);
    battle(player, slime);

    delete player;
    player = nullptr;
    return 0;
}
