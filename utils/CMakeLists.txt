project(main)
cmake_minimum_required(VERSION 2.6)

add_library("thread" STATIC thread.cc)
target_link_libraries("thread" pthread)

