add_library("action" STATIC hashtable/hashtable.c)
target_link_libraries("action" "thread")
