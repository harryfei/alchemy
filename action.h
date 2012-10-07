#ifndef ACTION_H_H_H
#define ACTION_H_H_H
#include "hashtable/hashtable.h"

typedef void (*CallBackFunction)();

class Action{
};

class ActionExecutor{

    public:
        ActionExecutor();
        ~ActionExecutor();
        bool exec_action(Action *action);

    protected:
        void bind(int action_type,CallBackFunction *function);
    private:
        hash_table_t *action_functions;
        CallBackFunction *getActionFunction(int action_type);

};



#endif
