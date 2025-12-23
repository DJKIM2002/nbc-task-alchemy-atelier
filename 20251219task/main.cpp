// Copyright (c) 2025 Dongju Kim

#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "AlchemyWorkshop.h"
using namespace std;  // NOLINT

static bool IsOnlySpaces(const string& str);
static void AddRecipeMenu(AlchemyWorkshop& myWorkshop);
static void SearchRecipeMenu(AlchemyWorkshop& myWorkshop);
static void DispensePotionMenu(AlchemyWorkshop& myWorkshop);
static void ReturnPotionMenu(AlchemyWorkshop& myWorkshop);

int main() {
  AlchemyWorkshop myWorkshop;

  myWorkshop.AddRecipe("체력 포션", {"빨간 약초", "물병"});
  myWorkshop.AddRecipe("마나 포션", {"파란 약초", "물병"});
  myWorkshop.AddRecipe("스테미나 포션", {"노란 약초", "물병"});
  myWorkshop.AddRecipe("화염 내성 물약", {"화염꽃", "재", "물병"});

  while (true) {
    cout << "[ 연금술 공방 관리 시스템 ]\n";
    cout << "1. 레시피 추가\n";
    cout << "2. 모든 레시피 출력\n";
    cout << "3. 레시피 검색\n";
    cout << "4. 물약 지급\n";
    cout << "5. 공병 반환\n";
    cout << "6. 종료\n";
    cout << "선택 : ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
      cout << "* 잘못된 입력입니다. 숫자를 입력해주세요.\n";
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }

    switch (choice) {
      case 1:
        AddRecipeMenu(myWorkshop);
        break;
      case 2:
        myWorkshop.DisplayAllRecipes();
        break;
      case 3:
        SearchRecipeMenu(myWorkshop);
        break;
      case 4:
        DispensePotionMenu(myWorkshop);
        break;
      case 5:
        ReturnPotionMenu(myWorkshop);
        break;
      case 6:
        cout << "공방 문을 닫습니다...\n";
        return 0;
      default:
        cout << "* 잘못된 선택입니다. 다시 시도하세요.";
        break;
    }
    Sleep(1500);
    system("cls");
  }
}

static bool IsOnlySpaces(const string& str) {
  return all_of(str.begin(), str.end(),
                [](unsigned char c) { return isspace(c); });
}

static void AddRecipeMenu(AlchemyWorkshop& myWorkshop) {
  string name;
  cout << "물약 이름 : ";
  cin.ignore(10000, '\n');
  getline(cin, name);

  if (IsOnlySpaces(name)) {
    cout << "* 물약 이름은 공백일 수 없습니다. [레시피 추가]를 취소합니다.\n";
    return;
  }

  if (myWorkshop.SearchRecipeByName(name)) {
    cout << "* 이미 존재하는 레시피 이름입니다! [레시피 추가]를 취소합니다.\n";
    return;
  }

  vector<string> ingredients_input;
  string ingredient;
  cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)\n";
  while (true) {
    cout << "재료 입력 : ";
    getline(cin, ingredient);
    // 문자열이 공백 문자로만 이루어져 있으면 다시 입력 받기
    if (IsOnlySpaces(ingredient)) {
      cout << "* 재료 이름은 공백일 수 없습니다. 다시 입력해주세요.\n";
      continue;
    }

    // 이미 입력한 재료이면 다시 입력 받기
    if (find(ingredients_input.begin(), ingredients_input.end(), ingredient) !=
        ingredients_input.end()) {
      cout << "* 이미 입력한 재료입니다. 다른 재료를 입력해주세요.\n";
      continue;
    }

    if (ingredient == "끝") {
      break;
    }
    ingredients_input.push_back(ingredient);
  }

  if (!ingredients_input.empty()) {
    myWorkshop.AddRecipe(name, ingredients_input);
  } else {
    cout << "* 재료가 입력되지 않아 [레시피 추가]를 취소합니다.\n";
  }
}

static void SearchRecipeMenu(AlchemyWorkshop& myWorkshop) {
  cout << "\n--- [ 레시피 검색 ] ---\n";
  cout << "1. 이름으로 검색\n";
  cout << "2. 재료로 검색\n";
  cout << "선택 : ";

  int searchChoice;
  cin >> searchChoice;

  if (cin.fail()) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "* 잘못된 입력입니다.\n";
    return;
  }
  cin.ignore(10000, '\n');

  if (searchChoice == 1) {
    string name;
    cout << "검색할 물약 이름 : ";
    getline(cin, name);

    auto result = myWorkshop.SearchRecipeByName(name);

    if (result) {
      cout << ">> '" << name << "' 레시피를 찾았습니다!\n";
      cout << ">> 물약 이름 '" << name << "\n";
      cout << "- 필요 재료 : ";
      vector<string> IngredientList = result->GetIngredients();
      for (const auto& ingredient : IngredientList) {
        cout << ingredient;
        if (ingredient != IngredientList.back()) {
          cout << ", ";
        }
      }
      cout << "\n";
      cout << "- 현재 재고 : " << myWorkshop.GetStockByName(name) << "개\n";
    } else {
      cout << "* '" << name << "' 레시피를 찾을 수 없습니다.\n";
    }
  } else if (searchChoice == 2) {
    string ingredient;
    cout << "검색할 재료 이름을 한 가지만 입력하세요 : ";
    getline(cin, ingredient);

    auto results = myWorkshop.SearchRecipeByIngredient(ingredient);

    if (!results.empty()) {
      cout << ">> 재료 '" << ingredient << "'를(을) 포함하는 레시피를 "
           << results.size() << "개 찾았습니다!\n";
      for (const auto& recipe : results) {
        cout << "- 물약 이름 : " << recipe->GetName() << "\n";
        cout << "  > 필요 재료 : ";
        vector<string> IngredientList = recipe->GetIngredients();
        for (const auto& ingredient : IngredientList) {
          cout << ingredient;
          if (ingredient != IngredientList.back()) {
            cout << ", ";
          }
        }
        cout << "\n";
      }
    } else {
      cout << "* 재료 '" << ingredient
           << "'를(을) 포함하는 레시피를 찾을 수 없습니다.\n";
    }
  } else {
    cout << "* 잘못된 선택입니다. 메인 메뉴로 돌아갑니다.\n";
  }
}

static void DispensePotionMenu(AlchemyWorkshop& myWorkshop) {
  cout << "\n--- [ 물약 지급 ] ---\n";
  cout << "1. 이름으로 검색 후 지급\n";
  cout << "2. 재료로 검색 후 지급\n";
  cout << "선택 : ";
  int dispenseChoice;
  cin >> dispenseChoice;
  if (cin.fail()) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "* 잘못된 입력입니다.\n";
    return;
  }
  cin.ignore(10000, '\n');
  if (dispenseChoice == 1) {
    string name;
    cout << "지급할 물약 이름 : ";
    getline(cin, name);
    myWorkshop.DispensePotionByName(name);
  } else if (dispenseChoice == 2) {
    string ingredient;
    cout << "재료 이름을 한 가지만 입력하세요 : ";
    getline(cin, ingredient);
    auto dispensedPotions = myWorkshop.DispensePotionsByIngredient(ingredient);
    if (!dispensedPotions.empty()) {
      cout << ">> 다음 물약들이 지급되었습니다:\n";
      for (const auto& potionName : dispensedPotions) {
        cout << "- " << potionName << "\n";
      }
    } else {
      cout << "* 해당 재료를 포함하는 물약의 재고가 없습니다.\n";
    }
  } else {
    cout << "* 잘못된 선택입니다. 메인 메뉴로 돌아갑니다.\n";
  }
}

static void ReturnPotionMenu(AlchemyWorkshop& myWorkshop) {
  string name;
  cout << "반환할 물약 이름 : ";
  cin.ignore(10000, '\n');
  getline(cin, name);
  myWorkshop.ReturnPotionByName(name);
}