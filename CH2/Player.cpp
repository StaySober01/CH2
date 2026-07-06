#include "player.h"
#include <iostream>

Player::Player(const std::string& name, int hp, int mp, int power, int defence)
    : name(name), job("None"), level(1), hp(hp), mp(mp), power(power),
      defence(defence), curHpPotion(0), curMpPotion(0) {}

const std::string& Player::getName() const { return name; }
const std::string& Player::getJob() const { return job; }
int Player::getLevel() const { return level; }
int Player::getHp() const { return hp; }
int Player::getMp() const { return mp; }
int Player::getPower() const { return power; }
int Player::getDefence() const { return defence; }
void Player::setName(const std::string& value) { name = value; }
void Player::setJob(const std::string& value) { job = value; }
void Player::setLevel(int value) { level = value; }
void Player::setHp(int value) { hp = value; }
void Player::setMp(int value) { mp = value; }
void Player::setPower(int value) { power = value; }
void Player::setDefence(int value) { defence = value; }

void Player::printPlayerStatus() const {
    std::cout << "------------------------------------\n"
              << "Name: " << name << " | Job: " << job << " | Lv." << level << '\n'
              << "HP: " << hp << " | MP: " << mp << " | Attack: " << power
              << " | Defense: " << defence << '\n'
              << "------------------------------------\n";
}

void Player::takeDamage(int damage) { hp -= damage; }
void Player::consumeMp(int amount) { mp -= amount; }
void Player::gainHpPotion(int amount) { curHpPotion += amount; }
void Player::gainMpPotion(int amount) { curMpPotion += amount; }

void Player::useHpPotion() {
    if (curHpPotion <= 0) {
        std::cout << "You don't have an HP potion.\n";
        return;
    }
    hp += 20;
    --curHpPotion;
    std::cout << "You recovered 20 HP. (HP potions: " << curHpPotion << ")\n";
}

void Player::useMpPotion() {
    if (curMpPotion <= 0) {
        std::cout << "You don't have an MP potion.\n";
        return;
    }
    mp += 20;
    --curMpPotion;
    std::cout << "You recovered 20 MP. (MP potions: " << curMpPotion << ")\n";
}
