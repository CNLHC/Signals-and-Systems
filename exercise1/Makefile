CC=gcc
CFLAGS=-g -I.
DEPS = convolution.c  
OBJ = convolution.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exercise: $(OBJ)
	gcc -g -o $@ $^ $(CFLAGS)
