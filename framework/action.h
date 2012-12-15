#ifndef ACTION_H_H_H
#define ACTION_H_H_H
#include "hashtable/hashtable.h"
#include "utils/thread.h"

class Action
{
    public:
        int action_type;
};


typedef Func0<void> ACTION_CB;
class ActionExecutor
{
    public:
        ActionExecutor();
        ~ActionExecutor();
        bool exec_action(Action action);

    protected:
        void bind(ACTION_CB func,int action_type);
        void send_action(Action action);
    private:
        hash_table_t *action_functions;
};


class ActionNode
{
    public:
        Action action;
        ActionNode *next;
};

class ActionQueue
{
    private:
        ActionNode *head;
        ActionNode *tail;
        int count;
        void fix_queue();
    public:
        ActionQueue();
        Action pull_action();
        void push_action(Action action);
        bool is_empty();

};

class ActionDispatcher
{
    private :
        hash_table_t *action_executors;
        int executor_count;
        ActionQueue action_queue;
        Thread *dispatch_thread;
        Mutex *action_queue_mutex;
        void dispatch_loop();
        ActionDispatcher();
        ~ActionDispatcher();
    public :
        static ActionDispatcher *get_instance();
        void add_executor(ActionExecutor *action_executor);
        void remove_executor(ActionExecutor *action_executor);
        void send_action(Action action);
};


#endif
