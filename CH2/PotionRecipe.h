#pragma once

#include <string>

struct PotionRecipe {
    std::string name;
    std::string firstIngredient;
    int firstIngredientCount;
    std::string secondIngredient;
    int secondIngredientCount;

    void PrintInfo() const;
    bool ContainsIngredient(const std::string& ingredient) const;
};
