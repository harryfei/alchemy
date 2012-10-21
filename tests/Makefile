.PHONY: all clean

test: all
	#./cardtest
	#./cardstest
	./actiontest

all: libunit++.a card_test.cc card_test.cc action_test.cc
	#g++ card_test.cc ../card.cc -o cardtest -Lunit++ -lunit++
	#g++ cards_test.cc ../card.cc ../card_array.cc -o cardstest -Lunit++ -lunit++
	g++ action_test.cc ../action.cc ../hashtable/hashtable.c -o actiontest -Lunit++ -lunit++
libunit++.a:
	$(MAKE) libunit++.a -C unit++
clean:
	rm cardstest
	rm cardtest
	rm actiontest
	rm unit++/unit++
	rm unit++/libunit++.a
	$(MAKE) clean -C unit++
