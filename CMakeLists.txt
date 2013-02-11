project(alchemy)
cmake_minimum_required(VERSION 2.6)
include_directories(
                    ${PROJECT_SOURCE_DIR}
                    )

enable_testing()
add_subdirectory(card)
add_subdirectory(trigger)
add_subdirectory(utils)
add_subdirectory(framework)
add_subdirectory(player)
add_subdirectory(lua)
add_subdirectory(tests)

find_package(PkgConfig)
#find_package(lua)

pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(LUA lua>=5.2)


link_directories(
    ${GTKMM_LIBRARY_DIRS}
    ${LUA_LIBRARY_DIRS}
)
include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIRS}
)

add_executable("main" main.cc game_manager.cc screen_manager.cc)
target_link_libraries("main" action player card  trigger luahelper ${GTKMM_LIBRARIES} ${LUA_LIBRARIES})
