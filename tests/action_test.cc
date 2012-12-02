#include "unit++/unit++.h"
#include "../action.h"
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "../delegate_tmpl.h"
using namespace std;
using namespace unitpp;
typedef void (ActionExecutor::* TEST)(void);
namespace {
    class TestExecutor : public ActionExecutor
    {
        public:
            int test;
            TestExecutor()
            {
                bind(member_func(this,&TestExecutor::action1),1);
                bind(member_func(this,&TestExecutor::action2),2);
                bind(member_func(this,&TestExecutor::action3),3);
            }
            void action1()
            {
                Action a1,a2,a3;
                a1.action_type =1;
                a2.action_type =2;
                a3.action_type =3;
                test = 1;
                send_action(a2);
                printf("action1\n");
            }
            void action2()
            {
                Action a1,a2,a3;
                a1.action_type =1;
                a2.action_type =2;
                a3.action_type =3;
                printf("action2\n");
                test = 2;
            }
            void action3()
            {
                test = 1;
                printf("action3\n");
            }
        //protected:
            //void run()
            //{
                //int i = 0;
                //for(i;i<50;i++)
                //{
                    //printf("%d\n",i);
                //}
            //}

    };

    class ActionTest : public suite
    {
        void testActionDispatcher()
        {
            TestExecutor test;
            Action a1;
            a1.action_type =1;

            ActionDispatcher *dispatcher = ActionDispatcher::get_instance();
            dispatcher->send_action(a1);

            sleep(1);

            assert_eq("content check1",2, test.test);

        }
        void testActionExecutor()
        {
            TestExecutor test;
            Action a1,a2,a3,a4;
            a1.action_type =1;
            a2.action_type =2;
            a3.action_type =3;
            a4.action_type =4;

            ActionDispatcher *dispatcher = ActionDispatcher::get_instance();
            dispatcher->send_action(a1);
            sleep(1);
            assert_eq("content check2",2, test.test);
            dispatcher->send_action(a3);
            sleep(1);
            assert_eq("content check3",1, test.test);
            dispatcher->send_action(a2);
            sleep(1);
            assert_eq("content check4",2, test.test);
            dispatcher->send_action(a4);
            sleep(1);
            assert_eq("content check5",2, test.test);
        }
        public:
        ActionTest() : suite("ActionTest")
        {
            add("ActionTest", testcase(this, "TestExecutor", &ActionTest::testActionExecutor));
            add("ActionTest", testcase(this, "TestDispacther", &ActionTest::testActionDispatcher));
            suite::main().add("ActionTest", this);
        }
    };

    ActionTest *theTest = new ActionTest();

}

