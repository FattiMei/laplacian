EXP_DIR = ./experiments
IMP_DIR = ./implementations


CC = g++
INCFLAGS = -I $(IMP_DIR)
OPTFLAGS = -O2


LIBS += -lm


SRCS = $(wildcard $(IMP_DIR)/*.h)


norm: $(SRCS) $(EXP_DIR)/norms.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ $(EXP_DIR)/norms.cpp $(LIBS)


solve: $(SRCS) $(EXP_DIR)/solving.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ $(EXP_DIR)/solving.cpp $(LIBS)


report: solve
	./solve > errors.csv
	python3.8 report.py errors.csv
