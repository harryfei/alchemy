#include <stdio.h>

#include "framework/action.h"
#include "framework/hashtable/hashtable.h"
#include "utils/thread.h"
#include "utils/delegate_tmpl.h"

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

void ActionExecutor::send_action(Action action)
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
    action_queue_mutex = new Mutex();
    action_executors = hash_table_new(MODE_COPY);
    executor_count = 0;
}

ActionDispatcher::~ActionDispatcher()
{
    hash_table_delete(action_executors);
    delete dispatch_thread;
    delete action_queue_mutex;
}
ActionDispatcher *ActionDispatcher::get_instance()
{
    static ActionDispatcher instance;
    return &instance;
}

void ActionDispatcher::add_executor(ActionExecutor *action_executor)
{
    int i = executor_count;
    HT_ADD(action_executors,&i,action_executor);
    executor_count++;
}

void ActionDispatcher::remove_executor(ActionExecutor *action_executor)
{
    HT_REMOVE(action_executors,action_executor);
    executor_count--;
}

void ActionDispatcher::send_action(Action action)
{
    action_queue_mutex->lock();
    action_queue.push_action(action);
    action_queue_mutex->unlock();

    if (!(dispatch_thread->is_running()))
    {
        dispatch_thread->start();
    }
}
void ActionDispatcher::dispatch_loop()
{
    while(!action_queue.is_empty())
    {

        action_queue_mutex->lock();
        Action action = action_queue.pull_action();
        action_queue_mutex->unlock();

        int i = 0;
        for(i;i<executor_count;i++)
        {
            ActionExecutor *executor = (ActionExecutor *)HT_LOOKUP(action_executors,&i);
            executor->exec_action(action);
        }
    }
}



ActionQueue::ActionQueue()
{
    head = NULL;
    tail = NULL;
    count = 0;
}

Action ActionQueue::pull_action()
{
    Action action = head->action;
    ActionNode *tmp = head;
    head = head->next;
    delete tmp;
    count--;
    fix_queue();
    return action;
}

void ActionQueue::push_action(Action action)
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
    fix_queue();
}

void ActionQueue::fix_queue(){
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

