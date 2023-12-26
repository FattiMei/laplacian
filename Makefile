CC = gcc
OPT = -O3 -march=native


LIBS += -lm

NMAX = 10000
DEFINE = -DNMAX=$(NMAX)


all:
	$(CC) -o test main.c norm.c laplacian.c experiment.c $(LIBS) $(OPT)


# all:
# 	$(CC) -o test_laplacian_naive $(DEFINE) main.c norm.c laplacian_naive.c $(LIBS) $(OPT)
# 	$(CC) -o test_laplacian_better_action $(DEFINE) main.c norm.c laplacian_better_action.c $(LIBS) $(OPT)
# 
# run: all
# 	./test_laplacian_naive > laplacian_naive.csv
# 	./test_laplacian_better_action > laplacian_better_action.csv
# 	octave --persist report.m laplacian_naive.csv laplacian_better_action.csv
