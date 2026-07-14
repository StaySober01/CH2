#include "Item.h"
#include <iostream>

void Item::PrintInfo() const {
    std::cout << name << " (" << price << "G)\n";
}

bool compareByPrice(const Item& a, const Item& b) {
    return a.price < b.price;
}
