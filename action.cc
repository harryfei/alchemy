#include "action.h"
#include "hashtable/hashtable.h"

ActionExecutor::ActionExecutor() {
    action_functions = hash_table_new(MODE_COPY);
}

ActionExecutor::~ActionExecutor() {
    hash_table_delete(action_functions);
}
void ActionExecutor::bind(int action_type,ActionCallBack function)
{
    HT_ADD(action_functions,&action_type,&function);
}

bool ActionExecutor::exec_action(int action) {
    ActionCallBack function = getActionFunction(action);
    if(function != NULL)
    {
        function();
    }
}
ActionCallBack ActionExecutor::getActionFunction(int action_type)
{
    void * f = HT_LOOKUP(action_functions,&action_type);
    if(f != NULL)
    {
        ActionCallBack *function = (ActionCallBack *)f;
        return *function;
    }else{
        return NULL;
    }
}
