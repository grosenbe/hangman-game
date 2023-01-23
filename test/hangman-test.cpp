#include <gtest/gtest.h>

#include "src/WordGuesser.h"
#include "src/WordTester.h"

using namespace hangman;
using std::vector;

class HangmanTestFixture : public ::testing::Test {
public:
};

TEST(HangmanTests, WordGuesserReadsDictionary) {
  WordTester tester("test");

  WordGuesser guesser(tester);

  EXPECT_TRUE(guesser.GetCurrentDictionarySize() > 0);

  std::string expectedGuess("----");
  EXPECT_EQ(expectedGuess, guesser.GetCurrentGuess());
}

int
main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
