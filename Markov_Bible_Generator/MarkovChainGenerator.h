#pragma once
#include <map>

std::map<std::string, double*> generateMarkovChain();
std::map<std::string, int> generateWordList(std::string&);
void formatText(std::string& text);