#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "AlchemyWorkshop.h"
#include "Archer.h"
#include "Item.h"
#include "Magician.h"
#include "Monster.h"
#include "Skeleton.h"
#include "Slime.h"
#include "Thief.h"
#include "Warrior.h"
#include "Zombie.h"

int calculateDamage(int power, int defence) {
    int damage = power - defence;
    return damage > 0 ? damage : 1;
}

void clearScreen() {
    std::system("cls");
}

void pauseScreen() {
    std::system("pause");
}

void setPotion(int count, int* p_HPPotion, int* p_MPPotion) {
    *p_HPPotion = count;
    *p_MPPotion = count;
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
        Item droppedItem{ monster.getDropItemName(), monster.getDropItemPrice() };
        std::cout << "\n★ Victory!\n";
        player->gainExp(monster.getExpReward());
        std::cout << "  -> Got: " << droppedItem.name << "!\n";

        if (player->addItem(droppedItem)) {
            std::cout << "  -> Saved to inventory.\n";
        }
        else {
            std::cout << "  -> Inventory is full.\n";
        }
    }
    else {
        std::cout << "\nDefeat... " << player->getName() << " has fallen.\n";
    }
}

void printInventory(const Player& player) {
    const std::vector<Item>& inventory = player.getInventory();
    std::cout << "\n[ Inventory (" << inventory.size() << '/'
              << Player::MAX_INVENTORY_SIZE << ") ]\n";

    if (inventory.empty()) {
        std::cout << "Inventory is empty.\n";
        return;
    }

    int itemNumber = 1;
    for (const Item& item : inventory) {
        std::cout << itemNumber++ << ". ";
        item.PrintInfo();
    }
}

void enterDungeon(Player* player) {
    clearScreen();
    std::cout << "=== Select Monster ===\n"
              << "1. Slime\n"
              << "2. Zombie\n"
              << "3. Skeleton\n"
              << "0. Back\n"
              << "\nChoose: ";

    int monsterChoice = -1;
    if (!(std::cin >> monsterChoice)) {
        std::cout << "Invalid input. Enter a number from 0 to 3.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    clearScreen();
    switch (monsterChoice) {
    case 1: {
        Slime slime;
        battle(player, slime);
        break;
    }
    case 2: {
        Zombie zombie;
        battle(player, zombie);
        break;
    }
    case 3: {
        Skeleton skeleton;
        battle(player, skeleton);
        break;
    }
    case 0:
        return;
    default:
        std::cout << "Invalid input. Enter a number from 0 to 3.\n";
        break;
    }
}

void openPotionWorkshop(const AlchemyWorkshop& workshop) {
    bool isWorkshopOpen = true;

    while (isWorkshopOpen) {
        clearScreen();
        std::cout << "=== Potion Shop ===\n"
                  << "1. Show all recipes\n"
                  << "2. Search by potion name\n"
                  << "3. Search by ingredient\n"
                  << "0. Go back\n"
                  << "\nChoose: ";

        int choice = -1;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Enter a number from 0 to 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pauseScreen();
            continue;
        }

        std::string searchText;
        switch (choice) {
        case 1:
            workshop.ShowAllRecipes();
            break;
        case 2:
            std::cout << "Search potion name: ";
            std::getline(std::cin >> std::ws, searchText);
            workshop.SearchByName(searchText);
            break;
        case 3:
            std::cout << "Search ingredient: ";
            std::getline(std::cin >> std::ws, searchText);
            workshop.SearchByIngredient(searchText);
            break;
        case 0:
            isWorkshopOpen = false;
            continue;
        default:
            std::cout << "Invalid input. Enter a number from 0 to 3.\n";
            break;
        }

        pauseScreen();
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

    clearScreen();
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
        pauseScreen();
        clearScreen();
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

    int HPPotion = 0;
    int MPPotion = 0;
    setPotion(5, &HPPotion, &MPPotion);
    player->gainHpPotion(HPPotion);
    player->gainMpPotion(MPPotion);
    std::cout << "* You received 5 HP Potions and 5 MP Potions.\n";
    pauseScreen();

    bool isGameStart = false;
    while (!isGameStart) {
        clearScreen();
        std::cout << "============================================\n"
                  << "< Character Upgrade >\n"
                  << "1. HP UP    2. MP UP    3. Power x2\n"
                  << "4. Defence x2  5. Show Status  0. Start Game\n"
                  << "============================================\n"
                  << "Choose: ";

        int choice = -1;
        if (!(std::cin >> choice) || choice < 0 || choice > 5) {
            std::cout << "Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pauseScreen();
            continue;
        }

        switch (choice) {
        case 1: player->useHpPotion(); break;
        case 2: player->useMpPotion(); break;
        case 3:
            player->setPower(player->getPower() * 2);
            std::cout << "Power doubled.\n";
            break;
        case 4:
            player->setDefence(player->getDefence() * 2);
            std::cout << "Defence doubled.\n";
            break;
        case 5: player->printPlayerStatus(); break;
        case 0: std::cout << "Game Start!\n"; isGameStart = true; break;
        }

        if (!isGameStart) pauseScreen();
    }

    AlchemyWorkshop workshop;
    bool isRunning = true;

    while (isRunning) {
        clearScreen();
        std::cout << "=== Main Menu ===\n"
                  << "1. Enter Dungeon\n"
                  << "2. Check Inventory\n"
                  << "3. Potion Workshop\n"
                  << "0. Quit\n"
                  << "\nChoose: ";

        int menuChoice = -1;
        if (!(std::cin >> menuChoice)) {
            std::cout << "Invalid input. Enter a number from 0 to 3.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            pauseScreen();
            continue;
        }

        switch (menuChoice) {
        case 1: {
            if (player->getHP() <= 0) {
                std::cout << "You cannot enter the dungeon because your HP is 0.\n";
                break;
            }

            enterDungeon(player);
            break;
        }
        case 2:
            printInventory(*player);
            break;
        case 3:
            openPotionWorkshop(workshop);
            break;
        case 0:
            std::cout << "Goodbye!\n";
            isRunning = false;
            break;
        default:
            std::cout << "Invalid input. Enter a number from 0 to 3.\n";
            break;
        }

        if (isRunning) pauseScreen();
    }

    delete player;
    player = nullptr;
    return 0;
}
