// Copyright (c) 2025 Dongju Kim

#include <Windows.h>

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "AlchemyWorkshop.h"
using namespace std;  // NOLINT

static bool isOnlySpaces(const string& str);
static void addRecipeMenu(AlchemyWorkshop& myWorkshop);
static void searchRecipeMenu(AlchemyWorkshop& myWorkshop);

int main() {
  AlchemyWorkshop myWorkshop;

  while (true) {
    cout << "[ 연금술 공방 관리 시스템 ]\n";
    cout << "1. 레시피 추가\n";
    cout << "2. 모든 레시피 출력\n";
    cout << "3. 종료\n";
    cout << "4. 레시피 검색\n";
    cout << "선택 : ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
      cout << "잘못된 입력입니다. 숫자를 입력해주세요.\n";
      cin.clear();
      cin.ignore(10000, '\n');
      continue;
    }

    switch (choice) {
      case 1:
        addRecipeMenu(myWorkshop);
        break;
      case 2:
        myWorkshop.displayAllRecipes();
        break;
      case 4:
        searchRecipeMenu(myWorkshop);
        break;
      case 3:
        cout << "공방 문을 닫습니다...\n";
        return 0;
      default:
        cout << "잘못된 선택입니다. 다시 시도하세요.";
        break;
    }
    Sleep(1500);
    system("cls");
  }
}

static bool isOnlySpaces(const string& str) {
  return all_of(str.begin(), str.end(),
                [](unsigned char c) { return isspace(c); });
}

static void addRecipeMenu(AlchemyWorkshop& myWorkshop) {
  string name;
  cout << "물약 이름 : ";
  cin.ignore(10000, '\n');
  getline(cin, name);

  if (isOnlySpaces(name)) {
    cout << ">> 물약 이름은 공백일 수 없습니다. 레시피 추가를 취소합니다.\n";
    return;
  }

  vector<string> ingredients_input;
  string ingredient;
  cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)\n";
  while (true) {
    cout << "재료 입력 : ";
    getline(cin, ingredient);
    // 문자열이 공백 문자로만 이루어져 있으면 다시 입력 받기
    if (isOnlySpaces(ingredient)) {
      cout << ">> 재료 이름은 공백일 수 없습니다. 다시 입력해주세요.\n";
      continue;
    }

    // 이미 입력한 재료이면 다시 입력 받기
    if (find(ingredients_input.begin(), ingredients_input.end(), ingredient) !=
        ingredients_input.end()) {
      cout << ">> 이미 입력한 재료입니다. 다른 재료를 입력해주세요.\n";
      continue;
    }

    if (ingredient == "끝") {
      break;
    }
    ingredients_input.push_back(ingredient);
  }

  if (!ingredients_input.empty()) {
    myWorkshop.addRecipe(name, ingredients_input);
  } else {
    cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다.\n";
  }
}

static void searchRecipeMenu(AlchemyWorkshop& myWorkshop) {
  cout << "\n--- [ 레시피 검색 ] ---\n";
  cout << "1. 이름으로 검색\n";
  cout << "2. 재료로 검색\n";
  cout << "선택 : ";

  int searchChoice;
  cin >> searchChoice;

  if (cin.fail()) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "잘못된 입력입니다.\n";
    return;
  }
  cin.ignore(10000, '\n');

  if (searchChoice == 1) {
    string name;
    cout << "검색할 물약 이름 : ";
    getline(cin, name);

    const PotionRecipe* result = myWorkshop.searchRecipeByName(name);

    if (result != nullptr) {
      cout << ">> 레시피를 찾았습니다!\n";
      cout << "- 물약 이름 : " << result->getPotionName() << "\n";
      cout << "- 필요 재료 : ";
      for (const auto& ingredient : result->getIngredients()) {
        cout << ingredient << " ";
      }
      cout << "\n";
    } else {
      cout << ">> '" << name
           << "' 이름을 가진 물약 레시피를 찾을 수 없습니다.\n ";
    }
  } else if (searchChoice == 2) {
    string ingredient;
    cout << "검색할 재료 이름을 한 가지만 입력하세요 : ";
    getline(cin, ingredient);

    vector<PotionRecipe> results =
        myWorkshop.searchRecipeByIngredients(ingredient);

    if (!results.empty()) {
      cout << ">> 재료 '" << ingredient << "'를(을) 포함하는 레시피를 "
           << results.size() << "개 찾았습니다!\n";
      for (const auto& recipe : results) {
        cout << "- 물약 이름 : " << recipe.getPotionName() << "\n";
        cout << "  > 필요 재료 : ";
        vector<string> IngredientList = recipe.getIngredients();
        for (const auto& ingredient : IngredientList) {
          cout << ingredient;
          if (ingredient != IngredientList.back()) {
            cout << ", ";
          }
        }
        cout << "\n";
      }
    } else {
      cout << ">> 재료 '" << ingredient
           << "'를(을) 포함하는 레시피를 찾을 수 없습니다.\n";
    }
  } else {
    cout << "잘못된 선택입니다. 메인 메뉴로 돌아갑니다.\n";
  }
}