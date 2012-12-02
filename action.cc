#include <stdio.h>

#include "action.h"
#include "hashtable/hashtable.h"
#include "thread.h"
#include "delegate_tmpl.h"

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
    int type = action.action_type;

    void *f = HT_LOOKUP(action_functions,&type);
    if(f != NULL)
    {
        ACTION_CB *function = (ACTION_CB *)f;
        (*function)();
        return true;
    }
    else
    {
        return false;
    }
}

bool ActionExecutor::send_action(Action action)
{
    ActionDispatcher::get_instance()->send_action(action);
}

void ActionExecutor::bind(ACTION_CB func,int action_type)
{
    HT_ADD(action_functions,&action_type,&func);
}

ActionDispatcher::ActionDispatcher()
{
    dispatch_thread = new Thread(member_func(this,&ActionDispatcher::dispatch_loop));
}

ActionDispatcher::~ActionDispatcher()
{
    delete dispatch_thread;
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
    if (!(dispatch_thread->is_running()))
    {
        dispatch_thread->start();
    }
}
void ActionDispatcher::dispatch_loop()
{
    while(!action_queue.is_empty())
    {
        Action action = action_queue.pullAction();
        test_executor->exec_action(action);
    }
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

