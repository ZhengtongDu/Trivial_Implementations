CPP = g++
CFLAGS = -Wall -g -std=c++11
# Change these three name "include", "main" and "test"
INCLUDE = point2
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
	rm -f *.o

clean:
	rm -f *.o *~ *.out
