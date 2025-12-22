#pragma once

// Copyright (c) 2025 Dongju Kim
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "IStockManager.h"
#include "PotionRecipe.h"
using namespace std;  // NOLINT

class StockManager : public IStockManager {
 private:
  map<string, int> potionStock_;  // <재고 이름, 수량>

 public:
  static const int MAX_STOCK = 3;

  // 초기 재고 설정(레시피 추가 시 자동으로 3개 재고 세팅)
  void InitializeStock(const string& potionName) override {
    potionStock_[potionName] = MAX_STOCK;
    cout << ">> '" << potionName << "' 의 재고가 " << MAX_STOCK
         << "개로 초기화되었습니다.\n";
  }

  // 재고가 있다면 지급하고 true, 아니면 false
  bool DispensePotion(const string& potionName) override {
    auto it = potionStock_.find(potionName);
    if (it != potionStock_.end() && it->second > 0) {
      --(it->second);
      cout << ">> '" << potionName
           << "' 물약이 지급되었습니다. 남은 재고: " << it->second << "개\n";
      return true;
    } else {
      cout << "* '" << potionName << "' 물약의 재고가 부족합니다.\n";
      return false;
    }
  }

  // 공병 반환
  void ReturnPotion(const string& potionName) override {
    auto it = potionStock_.find(potionName);
    if (it != potionStock_.end()) {
      if (it->second < MAX_STOCK) {
        ++(it->second);
        cout << ">> '" << potionName
             << "' 공병을 반환 받았습니다. 현재 재고: " << it->second << "개\n";
      } else {
        cout << "* '" << potionName
             << "'의 재고가 이미 최대치입니다. 반환할 수 없습니다.\n";
      }
    } else {
      cout << "* '" << potionName
           << "' 은(는) 존재하지 않는 물약입니다. 반환할 수 없습니다.\n";
    }
  }

  // 현재 재고 조회(없으면 0)
  int GetStock(const string& potionName) const override {
    auto it = potionStock_.find(potionName);
    return (it != potionStock_.end()) ? it->second : 0;
  }
};