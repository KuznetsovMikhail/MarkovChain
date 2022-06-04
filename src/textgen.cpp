// Copyright 2021 Kuznetsov Mikhail

#include "textgen.h"
#include <fstream>

std::vector<prefix> prefixes;
std::set<char> punctuationMarks = {'.', ',', ':', ';', '-',
'"', '?', '!', '(', ')', '/', '\\', '#', '*', '<', '>'};

bool createStateTab(std::string _fileIn,
                    std::map<prefix, std::vector<std::string>>* _statetab) {
  std::ifstream fin(_fileIn);
  if(!fin.is_open()) {
    return false;
  }
  prefix pref = {};
  for (int i = 0; !fin.eof(); i = std::min(i + 1, NPREF)) {
    std::string word;
    fin >> word;
    if (!erasePunctuationMarksAndCapitals(&word)) {
      continue;
    }
    if (i >= NPREF) {
      (*_statetab)[pref].push_back(word);
      prefixes.push_back(pref);
      pref.pop_front();
    }
    pref.push_back(word);
  }
  fin.close();
  return true;
}

bool erasePunctuationMarksAndCapitals(std::string* _word) {
  for (int i = 0; i < int((*_word).size()); i++) {
    if ((*_word)[i] >= 'A' && (*_word)[i] <= 'Z') {
      (*_word)[i] += 'a' - 'A';
    }
    else if (punctuationMarks.count((*_word)[i])) {
      (*_word).erase(i, 1);
      i--;
    }
  }
  if ((*_word).size()) {
    return true;
  }
  return false;
}

std::string generateText(const std::map<prefix,
                         std::vector<std::string>>& _statetab,
                prefix pref) {
  std::string result;
  if (!pref.size()) {
    pref = prefixes[std::rand() % prefixes.size()];
  }
  for(auto word : pref) {
    result += word + ' ';
  }
  for (int i = 0; i < (MAXGEN - NPREF); i++) {
    auto start = _statetab.find(pref);
    if (start == _statetab.end()) {
      continue;
    }
    std::string suff = start->second[std::rand() % start->second.size()];
    result += suff + ' ';
    pref.pop_front();
    pref.push_back(suff);
  }
  if (result.back() == ' ') {
    result.pop_back();
  }
  return result;
}
