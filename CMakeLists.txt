project(alchemy)
cmake_minimum_required(VERSION 2.6)
include_directories(
                    ${PROJECT_SOURCE_DIR}
                    )

enable_testing()
add_subdirectory(card)
add_subdirectory(utils)
add_subdirectory(framework)
add_subdirectory(player)
add_subdirectory(tests)

