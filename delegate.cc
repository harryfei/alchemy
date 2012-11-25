#include <stdio.h>

class Test;




class Test {

    public:
        typedef void(Test::*callback)();

        class TestCallBack{
            public:
                Test *p;
                Test::callback fun;
                void operator () () {(p->*fun)();}
        };
        void test(Test* p, callback c_fun){
            TestCallBack cb;
            cb.p = p;
            cb.fun = c_fun;
            cb();
        }
};

#define CALLBACK(fun) \
    reinterpret_cast<callback>((fun))

class SubTest : public Test{
    public:
        void test2(){
            printf("p\n");
        }
        void test3(){
            test(this,callback(&SubTest::test2));
        }

};

class SubTest2 : public Test{
    public:
        void test2(){
            printf("p\n");
        }
        void test3(){
            test(this,callback(&SubTest2::test2));
        }

};
int main(){
    SubTest t;
    t.test3();
    SubTest2 t2;
    t2.test3();
}
