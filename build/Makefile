BUILD_DIR = .
INC_DIR = ../include
SRC_DIR = ../src


CC = gcc
INCFLAGS = -I $(INC_DIR)
OPTFLAGS = -O2


LIBS += -lm


SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))


all: main


main: $(OBJS)
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ ../main.c $^ $(LIBS)


norm: $(OBJS)
	$(CC) $(INCFLAGS) $(OPTFLAGS) -o $@ ../norms.c $^ $(LIBS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCFLAGS) $(OPTFLAGS) -c -o $@ $<


clean:
	rm -f main
	rm -f *.o
