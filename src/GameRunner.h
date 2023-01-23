#pragma once

#include "WordGuesser.h"
#include <string>

namespace hangman {

  class GameRunner {
  public:
    GameRunner(const std::string &);
    int PlayGame(const std::string &);

  private:
    size_t numGamesCompleted = 0;

    WordGuesser guesser;
  };
}
