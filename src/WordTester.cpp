#include "WordTester.h"
#include "WordGuesser.h"

#include <cctype>
#include <locale>

using namespace hangman;

WordTester::WordTester(const string &aWord)
{
  for (const auto &c : aWord) {
    word += std::toupper(c);
  }
}

vector<int> WordTester::CheckGuess(const char &guess) {
  vector<int> positions;

  for (auto i = 0u; i < word.size(); ++i) {
    if (word[i] == guess) {
      positions.push_back(i);
    }
  }
  return positions;
}

