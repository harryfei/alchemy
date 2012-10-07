#include "unit++/unit++.h"
#include "../card.h"
#include "../card_array.h"
using namespace std;
using namespace unitpp;
namespace {
   class CardsTest : public suite
   {
           void testCardsAdd() {
               Card *card1 = new Card(1,"card1");
               Card *card2 = new Card(2,"card2");


               Cards *card_array = new Cards();
               card_array->add(card1);
               card_array->add(card2);

               assert_eq("content check",1, card_array->get_card(0)->id);
               assert_eq("content check","card1", card_array->get_card(0)->effect_string);
               assert_eq("content check",2, card_array->get_card(1)->id);
               assert_eq("content check","card2", card_array->get_card(1)->effect_string);
               delete card1;
               delete card2;
               delete card_array;
           }
           void testCardsRemove() {
               Card *card1 = new Card(1,"card1");
               Card *card2 = new Card(2,"card2");


               Cards *card_array = new Cards();
               card_array->add(card1);
               card_array->add(card2);

               assert_eq("content check",1, card_array->get_card(0)->id);
               assert_eq("content check","card1", card_array->get_card(0)->effect_string);
               assert_eq("content check",2, card_array->get_card(1)->id);
               assert_eq("content check","card2", card_array->get_card(1)->effect_string);
               card_array->remove(0);
               assert_eq("content check",2, card_array->get_card(0)->id);
               assert_eq("content check","card2", card_array->get_card(0)->effect_string);
               delete card1;
               delete card2;
               delete card_array;
           }
           void testCardsClear() {
               Card *card1 = new Card(1,"card1");
               Card *card2 = new Card(2,"card2");


               Cards *card_array = new Cards();
               card_array->add(card1);
               card_array->add(card2);

               assert_eq("content check",1, card_array->get_card(0)->id);
               assert_eq("content check","card1", card_array->get_card(0)->effect_string);
               assert_eq("content check",2, card_array->get_card(1)->id);
               assert_eq("content check","card2", card_array->get_card(1)->effect_string);
               card_array->clear();
               assert_eq("content check",0, card_array->size());
               delete card1;
               delete card2;
               delete card_array;
           }
           void testCardsWash() {
               Card *card1 = new Card(1,"card1");
               Card *card2 = new Card(2,"card2");
               Card *card3 = new Card(3,"card3");
               Card *card4 = new Card(4,"card4");
               Card *card5 = new Card(5,"card5");


               Cards *card_array = new Cards();
               card_array->add(card1);
               card_array->add(card2);
               card_array->add(card3);
               card_array->add(card4);
               card_array->add(card5);

               assert_eq("content check",1, card_array->get_card(0)->id);
               assert_eq("content check","card1", card_array->get_card(0)->effect_string);
               assert_eq("content check",2, card_array->get_card(1)->id);
               assert_eq("content check","card2", card_array->get_card(1)->effect_string);
               assert_eq("content check",3, card_array->get_card(2)->id);
               assert_eq("content check","card3", card_array->get_card(2)->effect_string);
               assert_eq("content check",4, card_array->get_card(3)->id);
               assert_eq("content check","card4", card_array->get_card(3)->effect_string);
               assert_eq("content check",5, card_array->get_card(4)->id);
               assert_eq("content check","card5", card_array->get_card(4)->effect_string);
               assert_eq("length check1",5, card_array->size());
               card_array->wash();
               assert_eq("length check2",5, card_array->size());
               delete card1;
               delete card2;
               delete card3;
               delete card4;
               delete card5;
               delete card_array;
           }
       public:
           CardsTest() : suite("CardsTest")
           {
               add("CardsAdd", testcase(this, "TestCardAdd", &CardsTest::testCardsAdd));
               add("CardsRemove", testcase(this, "TestCardRemove", &CardsTest::testCardsRemove));
               add("CardsClear", testcase(this, "TestCardClear", &CardsTest::testCardsClear));
               add("CardsWash", testcase(this, "TestCardWash", &CardsTest::testCardsWash));
               suite::main().add("CardsTest", this);
           }
   };

   CardsTest *theTest = new CardsTest();
}
