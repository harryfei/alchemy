#include "unit++/unit++.h"
#include "card/card.h"
#include <string>
using namespace std;
using namespace unitpp;
namespace {
   class CardTest : public suite
   {
           void testCardCreate() {
               Card *card1 = new Card(1,"card1");
               Card *card2 = new Card(2,"card2");
               assert_eq("content check",1, card1->id);
               assert_eq("content check","card1", card1->effect_string);
               assert_eq("content check",2, card2->id);
               assert_eq("content check","card2", card2->effect_string);
               delete card1;
               delete card2;
           }
       public:
           CardTest() : suite("CardTest")
           {
               add("CardCreate", testcase(this, "TestCardCreate", &CardTest::testCardCreate));
               suite::main().add("CardTest", this);
           }
   };


   CardTest *theTest = new CardTest();
}
