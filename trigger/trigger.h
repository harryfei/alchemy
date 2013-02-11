#ifndef TRIGGER_H_H_H_
#define TRIGGER_H_H_H_
#include "lua/lua_object.h"

class Trigger:public LuaBase
{
    public:
        Trigger();
        ~Trigger();
        int condition;
        int action;
};

#endif
