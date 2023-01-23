#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;
namespace hangman {
  class WordTester {
  public:
    WordTester(const string &);

    vector<int> CheckGuess(const char &);

    uint32_t GetWordSize() const { return word.size(); }

  private:
    string word;
  };
}
