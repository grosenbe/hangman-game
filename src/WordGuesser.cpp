#include "WordGuesser.h"
#include "WordTester.h"

#include <cctype>
#include <cstdint>
#include <fstream>
#include <locale>
#include <string>

using namespace hangman;

WordGuesser::WordGuesser(const WordTester &tester, const string &path) {
  currentGuess = "";
  for (auto i = 0u; i < tester.GetWordSize(); ++i) {
    currentGuess += "-";
  }

  InitializeDictionary(path);
  UpdateCounts();
}

void WordGuesser::Reset(const WordTester &tester) {
  currentGuess = "";
  for (auto i = 0u; i < tester.GetWordSize(); ++i) {
    currentGuess += "-";
  }

  numCorrectGuesses = 0;
  haveGuessedWord = false;
  InitializeDictionary("/usr/share/dict/words");
  guessedLetters.clear();
  letterCounts.clear();
  UpdateCounts();
}

void WordGuesser::InitializeDictionary(const string &path) {
  dictionary.clear();
  if (initialDict.empty()) {
    std::ifstream inputStream(path);
    std::string line;

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
        initialDict.push_back(entry);
      }
    }
  }

  for (const auto &w : initialDict) {
    if (w.size() == currentGuess.size()) {
      dictionary.push_back(w);
    }
  }
}

char WordGuesser::GuessLetter() {
  uint32_t maxCount = 0;
  char guess;
  for (const auto &p : letterCounts) {
    if (guessedLetters.find(p.first) == guessedLetters.end() &&
        p.second > maxCount) {
      guess = p.first;
      maxCount = p.second;
    }
  }
  guessedLetters.insert(guess);

  return guess;
}

const string &WordGuesser::GetCurrentGuess() { return currentGuess; }

void WordGuesser::Update(const std::vector<int> &positions,
                         const char &letter) {
  UpdateDictionary(positions, letter);
  UpdateCounts();
}

void WordGuesser::UpdateDictionary(const std::vector<int> &positions,
                                   const char &letter) {
  for (const auto &p : positions) {
    currentGuess[p] = letter;
  }

  numCorrectGuesses += positions.size();
  if (numCorrectGuesses == currentGuess.size()) {
    haveGuessedWord = true;
    return;
  }

  auto it = dictionary.begin();
  while (it != dictionary.end()) {
    bool erasedWord = false;
    for (const auto &p : positions) {
      auto word = *it;
      if (word[p] != letter) {
        dictionary.erase(it);
        erasedWord = true;
        break;
      }
    }

    if (!erasedWord) {
      ++it;
    }
  }

  UpdateCounts();
}

// update the count of each letter in the dictionary
void WordGuesser::UpdateCounts() {
  std::vector<uint32_t> availableIndices;
  for (auto i = 0u; i < currentGuess.size(); ++i) {
    if (currentGuess[i] == '-')
      availableIndices.push_back(i);
  }

  char currChar = 'A';
  while (currChar < 'A' + 26) {
    if (guessedLetters.find(currChar) != guessedLetters.end()) {
      letterCounts.at(currChar) = 0;
      ++currChar;
      continue; // don't bother counting letters we've guessed before
    }

    auto count = 0u;
    for (const auto &word : dictionary) {
      // rather than looping over the whole word, just look at the currently
      // open positions
      for (auto idx : availableIndices) {
        if (word[idx] == currChar)
          ++count;
      }
    }

    if (letterCounts.find(currChar) == letterCounts.end()) {
      letterCounts.insert({currChar, count});
    } else {
      letterCounts.at(currChar) = count;
    }

    ++currChar;
  }
}
