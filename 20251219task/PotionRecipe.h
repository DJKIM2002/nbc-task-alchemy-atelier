#pragma once

// Copyright (c) 2025 Dongju Kim
#include <memory>
#include <string>
#include <vector>
using namespace std;  // NOLINT

class AlchemyWorkshop;

class PotionRecipe {
 private:
  string name_;
  vector<string> ingredients_;

 public:
  PotionRecipe(const string& name, const vector<string>& ingredients)
      : name_(name), ingredients_(ingredients) {}
  const string& GetName() const { return name_; }
  const vector<string>& GetIngredients() const { return ingredients_; }
};
