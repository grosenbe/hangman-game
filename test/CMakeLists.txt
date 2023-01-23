add_executable(hangman-test hangman-test.cpp)

target_include_directories(hangman-test PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(hangman-test
  hangman
  pthread
  gtest
  )

