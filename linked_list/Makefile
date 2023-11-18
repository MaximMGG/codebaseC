MAIN = list
CC = gcc
CFLAGS = -Wall -Wextra

SRC = linked_list.c test_linked_list.c
OBJ = $(SRC:.c=.o)


$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o $(MAIN)

debug:
	$(CC) $(SRC) -g
