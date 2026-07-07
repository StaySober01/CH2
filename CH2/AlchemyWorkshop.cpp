#include "AlchemyWorkshop.h"
#include <iostream>

AlchemyWorkshop::AlchemyWorkshop()
    : recipes{
          { "HPPotion", "Herb", 1, "Clear Water", 1 },
          { "MPPotion", "Magic Herb", 1, "Clear Water", 1 },
          { "StaminaPotion", "Herb", 1, "Berry", 1 }
      } {}

void AlchemyWorkshop::ShowAllRecipes() const {
    std::cout << "\n[ All Potion Recipes ]\n";
    for (const PotionRecipe& recipe : recipes) {
        std::cout << "-> ";
        recipe.PrintInfo();
    }
}

void AlchemyWorkshop::SearchByName(const std::string& name) const {
    for (const PotionRecipe& recipe : recipes) {
        if (recipe.name == name) {
            std::cout << "-> ";
            recipe.PrintInfo();
            return;
        }
    }

    std::cout << "Can't find recipe.\n";
}

void AlchemyWorkshop::SearchByIngredient(const std::string& ingredient) const {
    int foundCount = 0;

    for (const PotionRecipe& recipe : recipes) {
        if (recipe.ContainsIngredient(ingredient)) {
            std::cout << "-> " << recipe.name << " ("
                      << recipe.firstIngredient << " x" << recipe.firstIngredientCount << ", "
                      << recipe.secondIngredient << " x" << recipe.secondIngredientCount << ")\n";
            ++foundCount;
        }
    }

    if (foundCount == 0) {
        std::cout << "찾을 수 없습니다\n";
        return;
    }

    std::cout << "Found " << foundCount << " recipes.\n";
}
