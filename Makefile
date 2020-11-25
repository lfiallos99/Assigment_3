F90 = f95
CC = gcc
FLAGS = -O3
FLAGS0 = -O0
FLAGS02= -O2
OBJS= Head.c tools.c
BINARY= SOLHEAD
BINARY2= soldebug
all: $(BINARY)

SOLHEAD: $(OBJS)
	$(CC) -o $(BINARY) $(FLAGS02)  $(OBJS)
	
soldebug: $(OBJS)
	$(CC) -g -o $(BINARY2) $(FLAGS0)  $(OBJS)

clean:
	rm -f $(BINARY) $(BINARY2)
	

		