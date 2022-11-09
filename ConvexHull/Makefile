CPP = g++
CFLAGS = -g -std=c++11
# CFLAGS = -Wall -g -std=c++11
# Change these three name "include", "main" and "test"
INCLUDE = ConvexHull
MAIN = main
TEST = test

.PHONY: clean all cl

all: main cl

main: $(MAIN).o $(INCLUDE).o
	$(CPP) $(CFLAGS) -o $(TEST).out $(MAIN).o

$(MAIN).o: $(INCLUDE).o
	$(CPP) $(CFLAGS) -c $(MAIN).cpp

$(INCLUDE).o: $(INCLUDE).h
	$(CPP) $(CFLAGS) -c $(INCLUDE).h

cl:
	rm -f *.o *.gch

clean: cl
	rm -f *~ *.out
