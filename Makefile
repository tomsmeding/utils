CXX=g++
CXXFLAGS=-Wall -O2 -std=c++11
BINARIES=q.seq q.repeat

.PHONY: all clean remake

all: $(BINARIES)
clean:
	rm -f $(BINARIES)
remake: clean all

q.seq: q.seq.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

q.repeat: q.repeat.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^