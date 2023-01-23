add_executable(hangman-demo main.cpp)

target_include_directories(hangman-demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(hangman-demo
  hangman)

