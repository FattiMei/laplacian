BUILD_DIR = .
INC_DIR = ../include
SRC_DIR = ../src
EXP_DIR = ../experiments
IMPL_DIR = ../implementations


CC = g++
INCFLAGS = -I $(INC_DIR) -I $(IMPL_DIR)
OPTFLAGS = -O2


LIBS += -lm


SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
EXPS = $(wildcard $(EXP_DIR)/*.c)


all: main


main: $(OBJS) $(EXP_DIR)/main.c
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ $^ $(LIBS)


norm: $(OBJS) $(EXP_DIR)/norms.cpp
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ $^ $(LIBS)


residual: $(OBJS) $(EXP_DIR)/residuals.c
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ $^ $(LIBS)


solve: $(OBJS) $(EXP_DIR)/solving.c
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ $^ $(LIBS)


report: solve
	./solve > errors.csv
	python3.8 ../report.py errors.csv


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCFLAGS) $(OPTFLAGS) -c -o $@ $<


clean:
	rm -f main
	rm -f *.o
