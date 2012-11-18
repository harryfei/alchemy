#ifndef ACTION_H_H_H
#define ACTION_H_H_H
#include "hashtable/hashtable.h"
#include "fastdelegate/FastDelegate.h"
#include <pthread.h>
using namespace fastdelegate;



class AsynRunner
{
    private:
        pthread_t pid;
        static void* start_thread(void *runner);
    protected:
        int start();
        virtual void run();
};

class Action
{
    public:
        int action_type;
};

typedef FastDelegate0<> ActionCallBack;
class ActionExecutor : public AsynRunner
{

    public:
        ActionExecutor();
        ~ActionExecutor();
        bool exec_action(Action action);

    protected:
        void bind(int action_type,ActionCallBack function);
        bool send_action(Action action);
    private:
        hash_table_t *action_functions;
        ActionCallBack get_action_function(int action_type);




};
//macro ACTION_BIND for using bind() and MakeDelegate() easy.
#define ACTION_BIND(action_type,callback) \
    bind(action_type,MakeDelegate(this,callback))


//class ExecutorNode{
    //public:
        //ActionExecutor *action_executor;
        //ExecutorNode *next;
        //ExecutorNode();
//};

class ActionDispatcher : public AsynRunner
{
    private :
        hash_table_t *action_executors;
        ActionExecutor *test_executor;
    public :
        static ActionDispatcher *get_instance();
        void add_executor(ActionExecutor *action_executor);
        void remove_executor(ActionExecutor *action_executor);
        void send_action(Action action);

};


#endif
