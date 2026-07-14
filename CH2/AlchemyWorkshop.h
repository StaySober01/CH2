#pragma once

#include <map>
#include <string>
#include <vector>
#include "PotionRecipe.h"

class AlchemyWorkshop {
private:
    static constexpr int MAX_STOCK = 3;
    std::vector<PotionRecipe> recipes;
    std::map<std::string, int> potionStock_;

public:
    AlchemyWorkshop();

    void AddRecipe(const PotionRecipe& recipe);
    bool DispensePotion(const std::string& name);
    bool ReturnPotion(const std::string& name);
    int GetStock(const std::string& name) const;
    void ShowAllRecipes() const;
    void SearchByName(const std::string& name) const;
    void SearchByIngredient(const std::string& ingredient) const;
};
