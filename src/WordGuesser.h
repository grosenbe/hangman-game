#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::vector;
using std::string;

namespace hangman {
  class WordTester;

  class WordGuesser {
  public:
    WordGuesser(const WordTester &, const string & = "/usr/share/dict/words");

    char GuessLetter();

    void Update(const std::vector<int> &, const char &);

    bool haveGuessedWord = false;

    const std::string& GetCurrentGuess();

    uint32_t GetCurrentDictionarySize() { return dictionary.size(); }

    void Reset(const WordTester &);
  
  private:
    vector<string> dictionary;
    vector<string> initialDict;
    string currentGuess;
    void InitializeDictionary(const std::string &);

    void UpdateCounts();
    void UpdateDictionary(const std::vector<int> &, const char &);
  
    std::unordered_map<char, uint32_t> letterCounts; // count of each letter in the dictionary
    std::unordered_set<char> guessedLetters;

    uint32_t numCorrectGuesses = 0;
  };
}
