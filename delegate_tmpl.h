#ifndef DELEGATE_TMPL_H_H_H_
#define DELEGATE_TMPL_H_H_H_
class NullClass {};

template <class R>
class Func0
{
    public:
        NullClass *obj;
        typedef R(NullClass::*NCFunc)(...);
        NCFunc function;
        R operator() ()
        {
            return (obj->*function)();
        }
};

template <class R,class P1>
class Func1
{
    public:
        NullClass *obj;
        typedef R(NullClass::*NCFunc)(...);
        NCFunc function;
        R operator() (P1 p1)
        {
            return (obj->*function)(p1);
        }
};

template <typename R,typename P1,typename P2>
class Func2
{
    public:
        NullClass *obj;
        typedef R(NullClass::*NCFunc)(...);
        NCFunc function;
        R operator() (P1 p1,P2 p2)
        {
            return (obj->*function)(p1, p2);
        }
};

template <typename R,typename P1,typename P2,typename P3>
class Func3
{
    public:
        NullClass *obj;
        typedef R(NullClass::*NCFunc)(...);
        NCFunc function;
        R operator() (P1 p1,P2 p2,P3 p3)
        {
            return (obj->*function)(p1,p2,p3);
        }
};

template <typename R,typename P1,typename P2,typename P3,typename P4>
class Func4
{
    public:
        NullClass *obj;
        typedef R(NullClass::*NCFunc)(...);
        NCFunc function;
        R operator() (P1 p1,P2 p2,P3 p3,P4 p4)
        {
            return (obj->*function)(p1,p2,p3,p4);
        }
};

template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5>
class Func5
{
    public:
        NullClass *obj;
        typedef R(NullClass::*NCFunc)(...);
        NCFunc function;
        R operator() (P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
        {
            return (obj->*function)(p1,p2,p3,p4,p5);
        }
};
template <typename Ret,typename T>
Func0<Ret>member_func(T *obj,Ret (T::*function)())
{
    Func0<Ret> f;
    typedef Ret(NullClass::*NCFunc)(...);
    f.obj = reinterpret_cast<NullClass*>(obj);
    f.function = reinterpret_cast<NCFunc>(function);
    return f;
}

template <typename Ret,typename T,typename P1>
Func1<Ret,P1>member_func(T *obj,Ret (T::*function)(P1))
{
    Func1<Ret,P1> f;
    typedef Ret(NullClass::*NCFunc)(...);
    f.obj = reinterpret_cast<NullClass*>(obj);
    f.function = reinterpret_cast<NCFunc>(function);
    return f;
}

template <typename Ret,typename T,typename P1,typename P2>
Func2<Ret,P1,P2>member_func(T *obj,Ret (T::*function)(P1,P2))
{
    Func2<Ret,P1,P2> f;
    typedef Ret(NullClass::*NCFunc)(...);
    f.obj = reinterpret_cast<NullClass*>(obj);
    f.function = reinterpret_cast<NCFunc>(function);
    return f;
}

template <typename Ret,typename T,typename P1,typename P2,typename P3>
Func3<Ret,P1,P2,P3>member_func(T *obj,Ret (T::*function)(P1,P2,P3))
{
    Func3<Ret,P1,P2,P3> f;
    typedef Ret(NullClass::*NCFunc)(...);
    f.obj = reinterpret_cast<NullClass*>(obj);
    f.function = reinterpret_cast<NCFunc>(function);
    return f;
}

template <typename Ret,typename T,typename P1,typename P2,typename P3,typename P4>
Func4<Ret,P1,P2,P3,P4>member_func(T *obj,Ret (T::*function)(P1,P2,P3,P4))
{
    Func4<Ret,P1,P2,P3,P4> f;
    typedef Ret(NullClass::*NCFunc)(...);
    f.obj = reinterpret_cast<NullClass*>(obj);
    f.function = reinterpret_cast<NCFunc>(function);
    return f;
}

template <typename Ret,typename T,typename P1,typename P2,typename P3,typename P4,typename P5>
Func5<Ret,P1,P2,P3,P4,P5>member_func(T *obj,Ret (T::*function)(P1,P2,P3,P4,P5))
{
    Func5<Ret,P1,P2,P3,P4,P5> f;
    typedef Ret(NullClass::*NCFunc)(...);
    f.obj = reinterpret_cast<NullClass*>(obj);
    f.function = reinterpret_cast<NCFunc>(function);
    return f;
}

#endif
