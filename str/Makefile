TARGET = string
CC = gcc
CFLAGS = -Wall -Wextra

SRC = testString.c my_string.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm *.o $(TARGET)

debug : 
	$(CC) $(SRC) -g
