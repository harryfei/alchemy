project(test)
cmake_minimum_required(VERSION 2.6)
add_subdirectory(unit++)
add_executable("actiontest" action_test.cc)
target_link_libraries("actiontest" "unit++" "action")
add_test("action"  ${CMAKE_CURRENT_BINARY_DIR}/actiontest)

add_executable("cardtest" card_test.cc)
target_link_libraries("cardtest" "unit++" "card")
add_test("card"  ${CMAKE_CURRENT_BINARY_DIR}/cardtest)

add_executable("cardstest" cards_test.cc)
target_link_libraries("cardstest" "unit++" "card")

add_test("cards test" ${CMAKE_CURRENT_BINARY_DIR}/cardstest)
