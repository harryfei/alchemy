#include "action.h"
#include "hashtable/hashtable.h"
#include <stdio.h>

ActionExecutor::ActionExecutor()
{
    //init action function collection
    action_functions = hash_table_new(MODE_COPY);

    //add this action executor into dispatcher
    ActionDispatcher::get_instance()->add_executor(this);
}

ActionExecutor::~ActionExecutor()
{
    hash_table_delete(action_functions);
}

bool ActionExecutor::exec_action(Action action)
{
    ActionCallBack function = get_action_function(action.action_type);
    if(function != NULL)
    {
        function();
    }
}
void ActionExecutor::bind(int action_type,ActionCallBack function)
{
    HT_ADD(action_functions,&action_type,&function);
}
ActionCallBack ActionExecutor::get_action_function(int action_type)
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

bool ActionExecutor::send_action(Action action)
{
    ActionDispatcher::get_instance()->send_action(action);
}


ActionDispatcher *ActionDispatcher::get_instance()
{
    static ActionDispatcher instance;
    return &instance;
}

void ActionDispatcher::add_executor(ActionExecutor *action_executor)
{
    this->test_executor = action_executor;
    //HT_ADD(action_executors,action_executor,action_executor);
}

void ActionDispatcher::remove_executor(ActionExecutor *action_executor)
{
    HT_REMOVE(action_executors,action_executor);
}
void ActionDispatcher::send_action(Action action)
{
    test_executor->exec_action(action);
}

void *AsynRunner::start_thread(void *runner)
{
    AsynRunner *asynRunner = (AsynRunner *)runner;
    asynRunner->run();
}

int AsynRunner::start()
{
    if(pthread_create(&pid,NULL,start_thread,this) != 0)
    {
        return -1;
    }
    return 0;
}

void AsynRunner::run()
{
}
