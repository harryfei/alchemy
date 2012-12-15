add_library("action" STATIC action.cc  hashtable/hashtable.c)
target_link_libraries("action" "thread")
