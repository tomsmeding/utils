CXX=g++
CXXFLAGS=-Wall -O2 -std=c++11
FILES=$(shell echo q.*.cpp)
BINARIES=$(shell find q.*.cpp | sed 's/.cpp$$//')

.PHONY: all clean remake

all: $(BINARIES)
clean:
	rm -f $(BINARIES)
remake: clean all

main: $(FILES)
	$(CXX) $(CXXFLAGS) -o $(shell echo $^ | sed 's/.cpp$$//') $^
