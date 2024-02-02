CXX        = g++
CXXFLAGS   = -Wall -Werror -fopenmp
LIBS       = -lm
OPTFLAGS   = -O2
BENCHFLAGS = -lbenchmark -lpthread
INCLUDE    = -I ./src

PYTHON = python3.8


sources    = $(wildcard src/*.h) 
examples   = $(wildcard examples/*.cpp)
benchmarks = $(wildcard benchmarks/*.cpp)


targets    += $(patsubst %.cpp,build/%,$(examples))
targets    += $(patsubst %.cpp,build/%,$(benchmarks))


all: $(targets)


build/examples/%: examples/%.cpp $(sources)
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(OPTFLAGS) -o $@ $< $(LIBS)


build/benchmarks/%: benchmarks/%.cpp $(sources)
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(OPTFLAGS) -o $@ $< $(BENCHFLAGS) $(LIBS)


report: $(exe)
	$^ > build/report.csv
	$(PYTHON) report.py build/report.csv


.PHONY: clean
clean:
	rm -f $(targets)
