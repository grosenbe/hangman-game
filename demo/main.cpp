#include "src/GameRunner.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace hangman;

using std::string;
using std::vector;

vector<string> ReadDictionary();

struct SuccessRate {
  int numSuccesses;
  int numAttempts;
};

int main(int argc __attribute__((unused)),
         char **argv __attribute__((unused))) {

  auto dict = ReadDictionary();

  std::unordered_map<size_t, SuccessRate> successRates;

  std::cerr << "Number of words: " << dict.size() << std::endl;

  double pctComplete = 0;
  int count = 0;
  int tenthOfAPercent = dict.size() / 100 / 10;
  int nextPrintNum = tenthOfAPercent;
  auto gr = GameRunner(dict[0]);
  for (const auto &word : dict) {
    auto wordLength = word.size();
    auto status = gr.PlayGame(word);

    if (successRates.find(wordLength) == successRates.end()) {
      successRates.insert({wordLength, {status, 1}});
    } else {
      auto &sr = successRates.at(wordLength);
      ++(sr.numAttempts);
      sr.numSuccesses += status;
    }

    if (++count > nextPrintNum) {
      nextPrintNum += tenthOfAPercent;
      pctComplete += 0.1;
      std::cerr << "%" << pctComplete << std::endl;
    }
  }

  std::cerr << "Word length, Success rate" << std::endl;
  std::cerr << "-----------, ------------" << std::endl;
  for (auto k = successRates.begin(); k != successRates.end(); ++k) {
    std::cerr << k->first;
    std::cerr << ", ";
    std::cerr << static_cast<double>(k->second.numSuccesses) /
                     k->second.numAttempts * 100;
    std::cerr << std::endl;
  }

  return 0;
}

vector<string> ReadDictionary() {
  vector<string> dictionary;
  string line;
  std::ifstream inputStream("/usr/share/dict/words");

  while (std::getline(inputStream, line)) {
    std::string entry;
    bool containsPunct = false;

    for (auto c = 0u; c < line.size(); ++c) {
      if (!std::isalnum(line[c])) {
        containsPunct = true;
        continue;
      }
      entry += std::toupper(line[c]);
    }

    if (!containsPunct) {
      dictionary.push_back(entry);
    }
  }
  return dictionary;
}
