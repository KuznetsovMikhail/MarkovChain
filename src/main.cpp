// Copyright 2021 Kuznetsov Mikhail
#include <iostream>
#include <ctime>
#include <fstream>
#include "textgen.h"

int main() {
  srand(time(nullptr));
  std::map<prefix, std::vector<std::string>> statetab;  // префикс-суффиксы
  if (createStateTab("../data/input.txt", &statetab)) {
    std::cout << "StateTab was created!" << std::endl;
  }
  std::string result = generateText(statetab);
  std::ofstream fout("../data/output.txt");
  if (result.size() && fout.is_open()) {
    fout << result;
    std::cout << "Text was generated!" << std::endl;
  }
  return 0;
}


