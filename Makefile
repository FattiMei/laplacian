BUILD_DIR = ./build
EXP_DIR   = ./examples
SRC_DIR   = ./src
BENCH_DIR = ./benchmark


CC = g++
PYTHON = python3.11
INCFLAGS = -I $(SRC_DIR)
OPTFLAGS = -O2 -fopenmp


LIBS += -lm
BENCHFLAGS = -lbenchmark -lpthread


SRCS = $(wildcard $(SRC_DIR)/*.h)


norm: build $(SRCS) $(EXP_DIR)/norms.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $(BUILD_DIR)/$@ $(EXP_DIR)/norms.cpp $(LIBS)


solve: build $(SRCS) $(EXP_DIR)/solving.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $(BUILD_DIR)/$@ $(EXP_DIR)/solving.cpp $(LIBS)


refine: build $(SRCS) $(EXP_DIR)/refinement.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $(BUILD_DIR)/$@ $(EXP_DIR)/refinement.cpp $(LIBS)


# still need improvement to avoid recompilation of the experiments
report: build solve
	$(BUILD_DIR)/solve > $(BUILD_DIR)/errors.csv
	$(PYTHON) report.py $(BUILD_DIR)/errors.csv


bench: build
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $(BUILD_DIR)/$@ $(BENCH_DIR)/multifrontal.cpp $(LIBS) $(BENCHFLAGS)
	$(BUILD_DIR)/bench

build:
	mkdir -p $(BUILD_DIR)
