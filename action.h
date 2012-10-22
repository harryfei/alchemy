#ifndef ACTION_H_H_H
#define ACTION_H_H_H
#include "hashtable/hashtable.h"
#include "fastdelegate/FastDelegate.h"
using namespace fastdelegate;

class Action
{
    public:
        int action_type;
};

typedef FastDelegate0<> ActionCallBack;
class ActionExecutor
{

    public:
        ActionExecutor();
        ~ActionExecutor();
        bool exec_action(Action action);

    protected:
        void bind(int action_type,ActionCallBack function);
    private:
        hash_table_t *action_functions;
        ActionCallBack get_action_function(int action_type);

};
//macro ACTION_BIND for using bind() and MakeDelegate() easy.
#define ACTION_BIND(action_type,callback) \
    bind(action_type,MakeDelegate(this,callback))

class ActionDispatcher
{
    private :
        static ActionDispatcher *instantce;
        ActionExecutor action_executors[];
        void run();
    public :
        static void init();
        static void destroy();
        static ActionDispatcher *get_instance();
        void add_executor(ActionExecutor *action_executor);
        void send_action(Action action);

};


#endif
