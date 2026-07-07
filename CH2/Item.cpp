#include "Item.h"
#include <iostream>

void Item::PrintInfo() const {
    std::cout << name << " (" << price << "G)\n";
}
