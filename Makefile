EXP_DIR = ./experiments
IMP_DIR = ./implementations




CC = g++
INCFLAGS = -I $(INC_DIR)
OPTFLAGS = -O2


LIBS += -lm


SRCS = $(wildcard $(IMP_DIR)/*.h)


norm: $(SRCS)
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ $(EXP_DIR)/norms.cpp $(LIBS)
