BINARY = alloc 
CC = gcc
FLAGS = 
DEBUG = 
LIBS = 
SRC = ./alloctest.c ./allocator.c
OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(BINARY)

$(BINARY): $(OBJ)
	$(CC) -o $(BINARY) $^ $(FLAGS) $(LIBS) $(DEBUG)
%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS) $(LIBS) $(DEBUG)
clean: 
	rm $(BINARY) $(OBJ)
#r
