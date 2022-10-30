CPP = g++
CFLAGS = -Wall -g -std=c++11
# Change these three name "include", "main" and "test"
INCLUDE = 
MAIN = main
TEST = test

.PHONY: clean all cl

all: main cl

main: $(MAIN).o $(INCLUDE).o
	$(CPP) $(CFLAGS) -o $(TEST).out $(MAIN).o

$(MAIN).o: $(INCLUDE).o
	$(CPP) $(CFLAGS) -c $(MAIN).cpp

$(INCLUDE).o: $(INCLUDE).h #$(INCLUDE).cpp
	$(CPP) $(CFLAGS) -c #$(INCLUDE).cpp

cl:
	rm -f *.o

clean:
	rm -f *.o *~ *.out
