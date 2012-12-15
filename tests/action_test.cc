#include "unit++/unit++.h"
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "utils/delegate_tmpl.h"
#include "framework/action.h"
using namespace std;
using namespace unitpp;
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
            }
            void action2()
            {
                Action a1,a2,a3;
                a1.action_type =1;
                a2.action_type =2;
                a3.action_type =3;
                test = 2;
            }
            void action3()
            {
                test = 1;
            }

    };
    class TestExecutor2 : public ActionExecutor
    {
        public:
            int test;
            TestExecutor2()
            {
                bind(member_func(this,&TestExecutor2::action1),1);
                bind(member_func(this,&TestExecutor2::action2),2);
            }
            void action1()
            {
                Action a1,a2,a3;
                a1.action_type =1;
                test = 1;
            }
            void action2()
            {
                Action a1,a2,a3;
                a1.action_type =1;
                test = 2;
            }

    };

    ActionDispatcher *dispatcher = ActionDispatcher::get_instance();

    class ActionTest : public suite
    {

        void testActionDispatcher()
        {
            Action a1;

            a1.action_type = 1;

            TestExecutor test;

            dispatcher->send_action(a1);
            sleep(1);
            assert_eq("content check1",2, test.test);

        }
        void testActionExecutor()
        {
            Action a1,a2,a3,a4;

            a1.action_type = 1;
            a2.action_type =2;
            a3.action_type =3;
            a4.action_type =4;
            TestExecutor test;

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
        void testMutiplyExecutor()
        {
            Action a1;

            a1.action_type = 1;

            TestExecutor test1;
            TestExecutor2 test2;

            dispatcher->send_action(a1);
            sleep(1);
            assert_eq("content check6",2,test1.test);
            assert_eq("content check7",2,test2.test);

        }

        public:
            ActionTest() : suite("ActionTest")
            {
                add("ActionTest", testcase(this, "TestExecutor", &ActionTest::testActionExecutor));
                add("ActionTest", testcase(this, "TestDispacther", &ActionTest::testActionDispatcher));
                add("ActionTest", testcase(this, "TestMutiplyDispacther", &ActionTest::testMutiplyExecutor));
                suite::main().add("ActionTest", this);
            }
    };

    ActionTest *theTest = new ActionTest();

}

