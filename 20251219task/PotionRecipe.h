#pragma once

// Copyright (c) 2025 Dongju Kim
#include <string>
#include <vector>
using namespace std;  // NOLINT

class AlchemyWorkshop;

class PotionRecipe {
 private:
  string potionName;
  vector<string> ingredients;

 public:
  PotionRecipe(const string& name, const vector<string>& ingredients)
      : potionName(name), ingredients(ingredients) {}
  string getPotionName() const { return potionName; }
  vector<string> getIngredients() const { return ingredients; }
  friend class AlchemyWorkshop;
};
