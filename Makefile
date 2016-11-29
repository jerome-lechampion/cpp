str.o : str.h str.cpp
	g++ -c str.cpp

e9.o : str.h e9.cpp
	g++ -c e9.cpp

e9 : str.o e9.o
	g++ -o e9 str.o e9.o

