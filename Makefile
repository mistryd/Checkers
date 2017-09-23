main: main.cpp checkers.cpp board.cpp
	g++ -Wall -Werror -pedantic -O1 --std=c++11 main.cpp checkers.cpp board.cpp  -o main
	./main




# Disable built-in rules
.SUFFIXES:

clean :
	rm -vf main stats_tests stats_public_test *~ *.out
