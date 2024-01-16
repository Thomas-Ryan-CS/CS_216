Lab9 : Lab9.o SortingList.o autocomplete.o term.o
	g++ term.o autocomplete.o SortingList.o Lab9.o -o Lab9
Lab9.o : Lab9.cpp 
	g++ -c Lab9.cpp
SortingList.o : SortingList.cpp SortingList.h
	g++ -c SortingList.cpp
autocomplete.o : autocomplete.cpp autocomplete.h
	g++ -c autocomplete.cpp
term.o : term.cpp term.h
	g++ -c term.cpp
clean :
	rm -i *.o Lab9
