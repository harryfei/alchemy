#include "action.h"
#include "hashtable/hashtable.h"

ActionExecutor::ActionExecutor() {
    action_functions = hash_table_new(MODE_COPY);
}

ActionExecutor::~ActionExecutor() {
    hash_table_delete(action_functions);
}
void ActionExecutor::bind(int action_type,CallBackFunction *function) {
    HT_ADD(action_functions,&action_type,function);
}
