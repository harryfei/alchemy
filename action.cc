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
    action_queue.pushAction(action);
    if (!is_running())
    {
        start();
    }
}
void ActionDispatcher::run()
{
    while(!action_queue.is_empty())
    {
        //printf("%d\n",action_queue.is_empty());
        Action action = action_queue.pullAction();
        test_executor->exec_action(action);
    }
}
void AsynRunner::beside_run()
{
    running = true;
    run();
    running = false;
}
void *AsynRunner::start_thread(void *runner)
{
    AsynRunner *asynRunner = (AsynRunner *)runner;
    asynRunner->beside_run();
}
bool AsynRunner::is_running()
{
    return running;
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

ActionQueue::ActionQueue()
{
    head = NULL;
    tail = NULL;
    count = 0;
}

Action ActionQueue::pullAction()
{
    Action action = head->action;
    ActionNode *tmp = head;
    head = head->next;
    delete tmp;
    count--;
    fix();
    return action;
}
void ActionQueue::pushAction(Action action)
{
    if (tail == NULL)
    {
        ActionNode * tmp = new ActionNode;
        tmp->action = action;
        tmp->next = NULL;
        head = tmp;
        tail = tmp;
    }
    else
    {
        ActionNode * tmp = new ActionNode;
        tmp->action = action;
        tmp->next = NULL;
        tail->next = tmp;
        tail = tmp;
    }

    count++;
}

void ActionQueue::fix(){
    if (head==NULL || count == 0){
        head = NULL;
        tail = NULL;
        count = 0;
    }
}
bool ActionQueue::is_empty()
{
    if (count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
