// Copyright (c) 2025 Dongju Kim

#include "AlchemyWorkshop.h"

#include <iostream>
#include <string>
#include <vector>

#include "RecipeManager.h"
#include "StockManager.h"
using namespace std;  // NOLINT

AlchemyWorkshop::AlchemyWorkshop()
    : recipeManager_(make_unique<RecipeManager>()),
      stockManager_(make_unique<StockManager>()) {}

// 레시피 추가 + 자동으로 재고 3개 생성
void AlchemyWorkshop::AddRecipe(const string& potionName,
                                const vector<string>& ingredients) {
  auto recipe = recipeManager_->AddRecipe(potionName, ingredients);
  if (recipe) {
    stockManager_->InitializeStock(potionName);
    cout << ">> [성공] " << potionName
         << " 레시피가 추가되고 재고가 세팅되었습니다.\n";
  } else {
    cout << ">> [실패] 이미 존재하는 레시피 이름입니다.\n";
  }
}

// 현재 가지고 있는 모든 레시피와 재고 상황 출력
void AlchemyWorkshop::DisplayAllRecipes() const {
  const auto& all = recipeManager_->GetAllRecipes();
  if (all.empty()) {
    cout << "* 현재 등록된 레시피가 없습니다.\n";
    return;
  }
  cout << "------------------------------------------\n";
  for (const auto& r : all) {
    cout << "물약: " << r->GetName()
         << " | 재고: " << stockManager_->GetStock(r->GetName()) << "\n";
    cout << "재료: ";
    for (const auto& i : r->GetIngredients()) cout << i << " ";
    cout << "\n";
  }
  cout << "------------------------------------------\n";
}

// 이름으로 레시피 검색
shared_ptr<PotionRecipe> AlchemyWorkshop::SearchRecipeByName(
    const string& name) const {
  return recipeManager_->FindRecipeByName(name);
}

// 재료로 레시피 검색
vector<shared_ptr<PotionRecipe>> AlchemyWorkshop::SearchRecipeByIngredient(
    const string& ingredient) const {
  return recipeManager_->FindRecipesByIngredient(ingredient);
}

// 포션 이름을 매개변수로 받아 해당 포션의 재고 조회
int AlchemyWorkshop::GetStockByName(const string& potionName) const {
  return stockManager_->GetStock(potionName);
}

// 포션 이름으로 검색하여 재고 있으면 지급 처리하고 true, 없으면 false 반환
bool AlchemyWorkshop::DispensePotionByName(const string& potionName) const {
  return stockManager_->DispensePotion(potionName);
}

// 해당 재료를 포함하는 레시피들 중, 재고 있는 것들을 지급 처리
vector<string> AlchemyWorkshop::DispensePotionsByIngredient(
    const string& ingredient) {
  vector<string> dispensedPotions;
  // 1. 해당 재료가 포함된 모든 레시피를 찾음
  auto matchedRecipes = recipeManager_->FindRecipesByIngredient(ingredient);

  // 2. 찾은 물약들에 대해 재고가 있으면 지급
  for (const auto& recipe : matchedRecipes) {
    if (stockManager_->DispensePotion(recipe->GetName())) {
      dispensedPotions.push_back(recipe->GetName());
    }
  }
  return dispensedPotions;
}

// 포션 이름을 매개변수로 받아 해당 포션의 공병을 반환
void AlchemyWorkshop::ReturnPotionByName(const string& potionName) const {
  stockManager_->ReturnPotion(potionName);
}