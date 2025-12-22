#pragma once

// Copyright (c) 2025 Dongju Kim
#include <memory>
#include <string>
#include <vector>
using namespace std;  // NOLINT

#include "PotionRecipe.h"
#include "IRecipeManager.h"
#include "IStockManager.h"
#include "RecipeManager.h"
#include "StockManager.h"

class AlchemyWorkshop {
 private:
  // 인터페이스 포인터를 사용하여 의존성 주입
  unique_ptr<IRecipeManager> recipeManager_;
  unique_ptr<IStockManager> stockManager_;

 public:
  AlchemyWorkshop();

  // 레시피 추가 + 자동으로 재고 3개 생성
  void AddRecipe(const string& name, const vector<string>& ingredients);

  // 현재 가지고 있는 모든 레시피와 재고 상황 출력
  void DisplayAllRecipes() const;

  // 이름으로 레시피 검색
  shared_ptr<PotionRecipe> SearchRecipeByName(const string& name) const;

  // 재료로 레시피 검색
  vector<shared_ptr<PotionRecipe>> SearchRecipeByIngredient(
      const string& ingredient) const;

  // 포션 이름을 매개변수로 받아 해당 포션의 재고 조회
  int GetStockByName(const string& potionName) const;

  // 포션 이름으로 검색하여 재고 있으면 지급 처리하고 true, 없으면 false 반환
  bool DispensePotionByName(const string& potionName) const;

  // 해당 재료를 포함하는 레시피들 중, 재고 있는 것들을 지급 처리
  vector<string> DispensePotionsByIngredient(const string& ingredient);

  // 포션 이름을 매개변수로 받아 해당 포션의 공병을 반환
  void ReturnPotionByName(const string& potionName) const;
};
