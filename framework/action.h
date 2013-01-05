#ifndef ACTION_H_H_H
#define ACTION_H_H_H
#include "hashtable/hashtable.h"
#include "utils/thread.h"
enum ActionType
{
    ACTION_DISCARD=1,
    ACTION_SCORE_ADD,
    ACTION_WIN
};

class Action
{
    public:
        ActionType action_type;
        int action_data;
};


typedef Func1<void,int> ACTION_CB;
class ActionExecutor
{
    public:
        ActionExecutor();
        //don't need the virtual ,because we always relase the
        //object in the subclass
        ~ActionExecutor();
        bool exec_action(Action action);

    protected:
        void bind(ACTION_CB func,ActionType action_type);
        void send_action(ActionType action_type, int action_data);
    private:
        hash_table_t *action_functions;
};

class ActionNode;

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
