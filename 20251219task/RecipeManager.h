#pragma once

// Copyright (c) 2025 Dongju Kim
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "IRecipeManager.h"
#include "PotionRecipe.h"
using namespace std;  // NOLINT

class RecipeManager : public IRecipeManager {
 private:
  vector<shared_ptr<PotionRecipe>> recipes_;

 public:
  // 레시피 추가
  shared_ptr<PotionRecipe> AddRecipe(
      const string& name, const vector<string>& ingredients) override {
    if (FindRecipeByName(name) != nullptr) {
      return nullptr;
    }
    auto newRecipe = make_shared<PotionRecipe>(name, ingredients);
    recipes_.push_back(newRecipe);
    cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다.\n";
    return newRecipe;
  }

  // 이름으로 레시피 1개 검색
  shared_ptr<PotionRecipe> FindRecipeByName(const string& name) const override {
    for (const auto& r : recipes_) {
      if (r->GetName() == name) {
        return r;
      }
    }
    return nullptr;
  }

  // 재료로 레시피 여러 개 검색
  vector<shared_ptr<PotionRecipe>> FindRecipesByIngredient(
      const string& ingredient) const override {
    vector<shared_ptr<PotionRecipe>> foundRecipes;
    for (const auto& r : recipes_) {
      const auto& ingredientList = r->GetIngredients();
      if (find(ingredientList.begin(), ingredientList.end(), ingredient) !=
          ingredientList.end()) {
        foundRecipes.push_back(r);
      }
    }
    return foundRecipes;
  };

  // 전체 레시피 조회
  virtual const vector<shared_ptr<PotionRecipe>>& GetAllRecipes() const override {
    return recipes_;
  }
};
