#pragma once

#include <string>
#include <vector>
#include "PotionRecipe.h"

class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    AlchemyWorkshop();

    void ShowAllRecipes() const;
    void SearchByName(const std::string& name) const;
    void SearchByIngredient(const std::string& ingredient) const;
};
