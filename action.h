#ifndef ACTION_H_H_H
#define ACTION_H_H_H


class Action{


};
class AcitonExecutor{

    public:
        bool exec_action(Action *action);

    protected:
        void bind(int action_type,void *function);

};






#endif
