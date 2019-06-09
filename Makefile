#makefile -f makefile

all:

	gcc -fopenmp -o main 10_main.c -Wall -lm

clean:

	rm main outtxt_*

