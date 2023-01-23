#include "GameRunner.h"
#include "WordGuesser.h"
#include "WordTester.h"

#include <string>
#include <iostream>

using namespace hangman;

GameRunner::GameRunner(const std::string &initialWord)
  : guesser(WordTester(initialWord)) {
}

int GameRunner::PlayGame(const std::string &wordToGuess) {
  int numGuessesLeft = 6;
  WordTester tester(wordToGuess);

  if (numGamesCompleted > 0)
    guesser.Reset(tester);
  while (numGuessesLeft > 0 && !guesser.haveGuessedWord) {
    auto guess = guesser.GuessLetter();
    auto guessResult = tester.CheckGuess(guess);

    if (!guessResult.empty()) {
      guesser.Update(guessResult, guess);
    } else {
      --numGuessesLeft;
    }
  }

  ++numGamesCompleted;
  if (guesser.haveGuessedWord) {
    std::cout << "Congratulations! The word was " << guesser.GetCurrentGuess() << "!" << std::endl;
    return 1;
  } else {
    std::cout << "Too bad! The closest we got was " << guesser.GetCurrentGuess() << std::endl;
    return 0;
  }
}
