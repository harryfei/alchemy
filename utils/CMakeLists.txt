add_library("thread" STATIC thread.cc)
target_link_libraries("thread" pthread)

add_library("file" STATIC file.cc)
