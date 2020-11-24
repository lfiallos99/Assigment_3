F90 = f95
CC = gcc
FLAGS = -O3
FLAGS0 = -O0
FLAGS02= -O2
OBJS= Head.c tools.c
BINARY= SOLHEAD
all: $(BINARY)

SOLHEAD: $(OBJS)
	$(CC) -o $(BINARY) $(FLAGS02)  $(OBJS)

clean:
	rm -f $(BINARY)

		