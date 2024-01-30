CXX = g++
CXXFLAGS = -Wall -Werror -fopenmp
LIBS = -lm
OPTFLAGS = -O2
BENCHFLAGS = -lbenchmark -lpthread
INCLUDE = -I ./src


sources    = $(wildcard src/*.h) 
examples   = $(wildcard examples/*.cpp)
benchmarks = $(wildcard benchmarks/*.cpp)


targets += $(patsubst %.cpp,build/%,$(examples))
targets += $(patsubst %.cpp,build/%,$(benchmarks))


all: $(targets)


build/examples/%: examples/%.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(OPTFLAGS) -o $@ $^ $(LIBS)


build/benchmarks/%: benchmarks/%.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(OPTFLAGS) -o $@ $^ $(BENCHFLAGS) $(LIBS)


examples/%.cpp:   $(sources)
benchmarks/%.cpp: $(sources)


# report: build residuals
# 	$(BUILD_DIR)/residuals > $(BUILD_DIR)/errors_and_residuals.csv
# 	$(PYTHON) report.py $(BUILD_DIR)/errors_and_residuals.csv
