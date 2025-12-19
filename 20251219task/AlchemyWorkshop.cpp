// Copyright (c) 2025 Dongju Kim

#include "AlchemyWorkshop.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;  // NOLINT

void AlchemyWorkshop::addRecipe(const string& name,
                                const vector<string>& ingredients) {
  recipes.push_back(PotionRecipe(name, ingredients));
  cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다.\n";
}

void AlchemyWorkshop::displayAllRecipes() const {
  if (recipes.empty()) {
    cout << "아직 등록된 레시피가 없습니다.\n";
    return;
  }

  cout << "\n--- [ 전체 레시피 목록 ] ---\n";
  for (size_t i = 0; i < recipes.size(); ++i) {
    cout << "- 물약 이름 : " << recipes[i].potionName << "\n";
    cout << "  > 필요 재료 : ";

    for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
      cout << recipes[i].ingredients[j];
      if (j < recipes[i].ingredients.size() - 1) {
        cout << ", ";
      }
    }
    cout << "\n";
  }
  cout << "---------------------------\n";
}

const PotionRecipe* AlchemyWorkshop::searchRecipeByName(
    const string& name) const {
    for (const auto& recipe : recipes) {
        if (recipe.potionName == name) {
            return &recipe;
        }
    }
    return nullptr;
}

vector<PotionRecipe> AlchemyWorkshop::searchRecipeByIngredients(
    const string& targetIngredient) const {
    vector<PotionRecipe> foundRecipes;
    for (const auto& recipe : recipes) {
        const auto& ingredientList = recipe.getIngredients();
        if (find(ingredientList.begin(), ingredientList.end(), 
            targetIngredient) != ingredientList.end()) {
			foundRecipes.push_back(recipe);
		}
	}
	return foundRecipes;
}