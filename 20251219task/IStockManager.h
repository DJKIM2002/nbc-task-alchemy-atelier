#pragma once

// Copyright (c) 2025 Dongju Kim
#include <memory>
#include <string>
using namespace std;  // NOLINT

class IStockManager {
 public:
  virtual ~IStockManager() = default;
  
  // 초기 재고 설정(레시피 추가 시 자동으로 3개 재고 세팅)
  virtual void InitializeStock(const string& potionName) = 0;
  
  // 재고가 있다면 지급하고 true, 아니면 false
  virtual bool DispensePotion(const string& potionName) = 0;
  
  // 공병 반환
  virtual void ReturnPotion(const string& potionName) = 0;
  
  // 현재 재고 조회(없으면 0)
  virtual int GetStock(const string& potionName) const = 0;
};
