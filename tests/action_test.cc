#include "unit++/unit++.h"
#include "../action.h"
#include <stdio.h>
#include <string>
using namespace std;
using namespace unitpp;
typedef void (ActionExecutor::* TEST)(void);
namespace {
    class TestExecutor : public ActionExecutor
    {
        public:
            TestExecutor()
            {
                ACTION_BIND(1,&TestExecutor::action1);
                ACTION_BIND(2,&TestExecutor::action2);
            }
            void action1()
            {
                printf("action 1\n");
            }
            void action2()
            {
                printf("action 2\n");
            }

    };
    class ActionTest : public suite
    {
        void testActionExecutor()
        {
            TestExecutor test;
            Action a1 ,a2,a3;
            a1.action_type =1;
            a2.action_type =2;
            a3.action_type =3;

            test.exec_action(a1);
            test.exec_action(a2);
            test.exec_action(a3);
        }
        public:
        ActionTest() : suite("CardTest")
        {
            add("CardCreate", testcase(this, "TestCardCreate", &ActionTest::testActionExecutor));
            suite::main().add("ActionTest", this);
        }
    };

    ActionTest *theTest = new ActionTest();

}

