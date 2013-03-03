#set(Boost_INCLUDE_DIR /usr/include/)
#set(Boost_LIBRARY_DIR /usr/lib)
find_package(Boost COMPONENTS system thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

add_library("network" STATIC network.cc)
target_link_libraries("network" ${ENET_LIBRARIES} ${Boost_LIBRARIES})
add_executable("network_server" server.cc)
target_link_libraries("network_server" network)
add_executable("network_client" client.cc)
target_link_libraries("network_client" network)

