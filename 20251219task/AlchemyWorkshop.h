#pragma once

// Copyright (c) 2025 Dongju Kim
#include "PotionRecipe.h"

class AlchemyWorkshop {
 private:
  vector<PotionRecipe> recipes;

 public:
  void addRecipe(const string& name, const vector<string>& ingredients);

  void displayAllRecipes() const;

  const PotionRecipe* searchRecipeByName(const string& name) const;

  vector<PotionRecipe> searchRecipeByIngredients(
      const string& targetIngredient) const;
};
