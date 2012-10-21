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
                ACTION_BIND(1,&TestExecutor::hi);
            }
            void hi()
            {
                printf("fsfsff\n");
            }

    };
    class ActionTest : public suite
    {
        void testActionExecutor()
        {
            TestExecutor test;
            test.exec_action(2);
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

