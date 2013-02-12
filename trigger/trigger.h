#ifndef TRIGGER_H_H_H_
#define TRIGGER_H_H_H_
#include "lua/lua_object.h"
#include "base/manager_tmpl.h"

class Trigger:public LuaBase
{
    public:
        Trigger();
        ~Trigger();
        int condition;
        int action;
};
typedef Manager<Trigger> TriggerManager;
#endif
