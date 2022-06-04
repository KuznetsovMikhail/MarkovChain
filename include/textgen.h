// Copyright 2021 Kuznetsov Mikhail
#ifndef INCLUDE_TEXGEN_H_
#define INCLUDE_TEXGEN_H_
#include <deque>
#include <string>
#include <vector>
#include <map>
#include <set>

typedef std::deque<std::string> prefix;          //  очередь префиксов
const int NPREF = 2;   //  количество слов в префиксе
const int MAXGEN = 1000;   //  объем текста на выходе
bool createStateTab(std::string _fileIn,
                    std::map<prefix, std::vector<std::string>>* _statetab);
std::string generateText(const std::map<prefix,
                         std::vector<std::string>>& _statetab,
                prefix pref = {});
bool erasePunctuationMarksAndCapitals(std::string* _word);

#endif  // INCLUDE_TEXGEN_H_
