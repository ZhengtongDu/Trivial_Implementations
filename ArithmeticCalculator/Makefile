CPP = g++
CFLAGS = -g -std=c++11
# CFLAGS = -Wall -g -std=c++11
# Change these three name "include", "main" and "test"
INCLUDE = ArithmeticCalculator
MAIN = main
TEST = test

.PHONY: clean all cl

all: main cl

main: $(MAIN).o
	$(CPP) $(CFLAGS) -o $(TEST).out $(MAIN).o

$(MAIN).o: $(INCLUDE).h
	$(CPP) $(CFLAGS) -c $(MAIN).cpp

cl:
	rm -f *.o

clean:
	rm -f *.o *~ *.out
