#pragma once

#include <string>

struct Item {
    std::string name;
    int price;

    void PrintInfo() const;
};
