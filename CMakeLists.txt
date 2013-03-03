project(alchemy)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
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
add_subdirectory(network)
add_subdirectory(tests)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(LUA lua>=5.2)
pkg_check_modules(ENET libenet>=1.3.6)


link_directories(
    ${GTKMM_LIBRARY_DIRS}
    ${LUA_LIBRARY_DIRS}
    ${ENET_LIBRARY_DIRS}
)
include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIRS}
    ${ENET_LIBRARY_DIRS}
)

add_executable("main" main.cc game_manager.cc screen_manager.cc game_init.cc api.cc network_manager.cc)
target_link_libraries("main" action player card  trigger luahelper network "file" ${GTKMM_LIBRARIES} ${LUA_LIBRARIES})
