BUILD_DIR = ./build
EXP_DIR = ./examples
SRC_DIR = ./src


CC = g++
INCFLAGS = -I $(SRC_DIR)
OPTFLAGS = -O2


LIBS += -lm


SRCS = $(wildcard $(SRC_DIR)/*.h)


norm: $(SRCS) $(EXP_DIR)/norms.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $(BUILD_DIR)/$@ $(EXP_DIR)/norms.cpp $(LIBS)


solve: $(SRCS) $(EXP_DIR)/solving.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $(BUILD_DIR)/$@ $(EXP_DIR)/solving.cpp $(LIBS)


report: solve
	$(BUILD_DIR)/solve > $(BUILD_DIR)/errors.csv
	python3.8 report.py $(BUILD_DIR)/errors.csv
