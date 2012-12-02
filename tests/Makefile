.PHONY: all clean

test: all
	#./cardtest
	#./cardstest
	./actiontest

all: libunit++.a card_test.cc card_test.cc action_test.cc ../action.cc
	#g++ card_test.cc ../card.cc -o cardtest -Lunit++ -lunit++
	#g++ cards_test.cc ../card.cc ../card_array.cc -o cardstest -Lunit++ -lunit++
	g++ action_test.cc ../action.cc ../hashtable/hashtable.c ../thread.cc -o actiontest -Lunit++ -lunit++ -lpthread
libunit++.a:
	$(MAKE) libunit++.a -C unit++

#action_test:action.o
#action.o: ../action.cc ../action.h
	#g++ -c ../action.cc ../hashtable/hashtable.c
clean:
	#rm cardstest
	#rm cardtest
	#rm actiontest
	rm unit++/unit++
	rm unit++/libunit++.a
	$(MAKE) clean -C unit++
