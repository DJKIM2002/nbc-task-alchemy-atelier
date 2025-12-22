#pragma once

// Copyright (c) 2025 Dongju Kim
#include <memory>
#include <string>
#include <vector>

class PotionRecipe;

using namespace std;  // NOLINT

class IRecipeManager {
 public:
  // 상속받는 자식 객체에서 소멸자 호출을 보장하기 위해 가상 소멸자 선언
  virtual ~IRecipeManager() = default;

  // 레시피 추가 후, 저장된 레시피의 포인터를 반환
  // 이미 있는 레시피는 추가할 수 없음
  virtual shared_ptr<PotionRecipe> AddRecipe(
      const string& name, const vector<string>& ingredients) = 0;

  // 이름으로 레시피 1개 검색
  virtual shared_ptr<PotionRecipe> FindRecipeByName(
      const string& name) const = 0;

  // 재료로 레시피 여러 개 검색
  virtual vector<shared_ptr<PotionRecipe>> FindRecipesByIngredient(
      const string& ingredient) const = 0;

  // 전체 레시피 조회
  virtual const vector<shared_ptr<PotionRecipe>>& GetAllRecipes() const = 0;
};
