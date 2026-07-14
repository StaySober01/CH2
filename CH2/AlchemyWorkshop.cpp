#include "AlchemyWorkshop.h"
#include <iostream>

AlchemyWorkshop::AlchemyWorkshop() {
    AddRecipe({ "HPPotion", "Herb", 1, "Clear Water", 1 });
    AddRecipe({ "MPPotion", "Magic Herb", 1, "Clear Water", 1 });
    AddRecipe({ "StaminaPotion", "Herb", 1, "Berry", 1 });
}

void AlchemyWorkshop::AddRecipe(const PotionRecipe& recipe) {
    recipes.push_back(recipe);
    potionStock_[recipe.name] = MAX_STOCK;
}

bool AlchemyWorkshop::DispensePotion(const std::string& name) {
    auto stock = potionStock_.find(name);
    if (stock == potionStock_.end()) {
        std::cout << "-> Dispense failed: potion not found!\n";
        return false;
    }

    if (stock->second <= 0) {
        std::cout << "-> Dispense failed: out of stock!\n";
        return false;
    }

    --stock->second;
    std::cout << "-> Dispense " << name << "  (stock: " << stock->second << ")\n";
    return true;
}

bool AlchemyWorkshop::ReturnPotion(const std::string& name) {
    auto stock = potionStock_.find(name);
    if (stock == potionStock_.end()) {
        std::cout << "-> Return failed: potion not found!\n";
        return false;
    }

    if (stock->second >= MAX_STOCK) {
        std::cout << "-> Return failed: stock is full!\n";
        return false;
    }

    ++stock->second;
    std::cout << "-> Return empty bottle  (stock: " << stock->second << ")\n";
    return true;
}

int AlchemyWorkshop::GetStock(const std::string& name) const {
    auto stock = potionStock_.find(name);
    if (stock == potionStock_.end()) {
        return 0;
    }

    return stock->second;
}

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
