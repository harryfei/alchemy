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

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
)
include_directories(
    ${GTKMM_INCLUDE_DIRS}
)
add_executable("main" main.cc game_manager.cc screen_manager.cc)
target_link_libraries("main" action player card ${GTKMM_LIBRARIES})
