#ifndef ACTION_H_H_H_
#define ACTION_H_H_H_
#include "utils/sigslot.h"
namespace Action{
class NetPacket{
    public:
        int type;
};
};
template <int type_id>
class Action0{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal0<> Signal;
        class NetPacket:public Action::NetPacket{
            public:
                NetPacket(){
                    type = type_id;
                }
        };
};

template <typename T1,int type_id>
class Action1{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal1<T1> Signal;
        class NetPacket:public Action::NetPacket {
            //int type;
            public:
                T1 arg1;
                NetPacket(){
                    type = type_id;
                }
        };
};

template <typename T1,typename T2,int type_id>
class Action2{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal2<T1,T2> Signal;
        class NetPacket:public Action::NetPacket{
            public:
                T1 arg1;
                T2 arg2;
                NetPacket(){
                    type = type_id;
                }
        };
};

template <typename T1,typename T2,typename T3,int type_id>
class Action3{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal3<T1,T2,T3> Signal;
        class NetPacket:public Action::NetPacket{
            public:
                T1 arg1;
                T2 arg2;
                T3 arg3;
                NetPacket(){
                    type = type_id;
                }
        };
};
template <typename T1,typename T2,typename T3, typename T4,int type_id>
class Action4{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal4<T1,T2,T3,T4> Signal;
        class NetPacket:public Action::NetPacket{
            public:
                T1 arg1;
                T2 arg2;
                T3 arg3;
                T4 arg4;
                NetPacket(){
                    type = type_id;
                };
        };
};
template <typename T1,typename T2,typename T3, typename T4,typename T5,int type_id>
class Action5{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal5<T1,T2,T3,T4,T5> Signal;
        class NetPacket:public Action::NetPacket{
            public:
                T1 arg1;
                T2 arg2;
                T3 arg3;
                T4 arg4;
                T5 arg5;
                NetPacket(){
                    type = type_id;
                };
        };
};
template <typename T1,typename T2,typename T3, typename T4,typename T5,typename T6,int type_id>
class Action6{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal6<T1,T2,T3,T4,T5,T6> Signal;
        class NetPacket:public Action::NetPacket{
            public:
                T1 arg1;
                T2 arg2;
                T3 arg3;
                T4 arg4;
                T5 arg5;
                T6 arg6;
                NetPacket(){
                    type = type_id;
                };
        };
};
template <typename T1,typename T2,typename T3, typename T4,typename T5,typename T6,typename T7,int type_id>
class Action7{
    public:
        const static int TYPE_ID = type_id;
        typedef sigslot::signal7<T1,T2,T3,T4,T5,T6,T7> Signal;
        class NetPacket:public Action::NetPacket{
            public:
                T1 arg1;
                T2 arg2;
                T3 arg3;
                T4 arg4;
                T5 arg5;
                T6 arg6;
                T7 arg7;
                NetPacket(){
                    type = type_id;
                };
        };
};
#endif
