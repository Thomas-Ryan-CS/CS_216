Lab8 : term.o TermSortingList.o Lab8.o
	g++ term.o TermSortingList.o Lab8.o -o Lab8

term.o : term.cpp term.h
	g++ -c term.cpp

TermSortingList.o : TermSortingList.cpp TermSortingList.h
	g++ -c TermSortingList.cpp

Lab8.o : Lab8.cpp
	g++ -c Lab8.cpp

clean :
	rm -i *.o Lab8
