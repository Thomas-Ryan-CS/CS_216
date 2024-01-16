Project2 : PA2.o SortingList.o autocomplete.o term.o
	g++ term.o autocomplete.o SortingList.o PA2.o -o Project2
PA2.o : PA2.cpp 
	g++ -c PA2.cpp
SortingList.o : SortingList.cpp SortingList.h
	g++ -c SortingList.cpp
autocomplete.o : autocomplete.cpp autocomplete.h
	g++ -c autocomplete.cpp
term.o : term.cpp term.h
	g++ -c term.cpp
clean :
	rm -i *.o Project2
