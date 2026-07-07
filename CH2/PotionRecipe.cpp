#include "PotionRecipe.h"
#include <iostream>

void PotionRecipe::PrintInfo() const {
    std::cout << name << ": "
              << firstIngredient << " x" << firstIngredientCount << ", "
              << secondIngredient << " x" << secondIngredientCount << '\n';
}

bool PotionRecipe::ContainsIngredient(const std::string& ingredient) const {
    return firstIngredient == ingredient || secondIngredient == ingredient;
}
