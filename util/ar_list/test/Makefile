BINARY = test
CC = gcc
FLAGS = 
DEBUG = -g
LIBS = -lassert -l_util
SRC = ./m_list_test.c ../m_list.c
OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(BINARY)

$(BINARY): $(OBJ)
	$(CC) -o $(BINARY) $^ $(FLAGS) $(LIBS) $(DEBUG)
%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS) $(LIBS) $(DEBUG)
clean: 
	rm $(BINARY) $(OBJ)
#r
