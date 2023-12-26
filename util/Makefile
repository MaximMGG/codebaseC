AR_LIST_DIR = ar_list/
QUEUE_DIR = queue/
OBJ_DIR = obj/

ALL = libutil.a deploy

SRC = $(wildcard $(AR_LIST_DIR)*.c $(QUEUE_DIR)*.c) 
OBJ = $(patsubst $(AR_LIST_DIR)%.c $(QUEUE_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

deploy: libutil.a
	sudo mkdir -p /usr/local/include/util
	sudo cp libutil.a /usr/local/lib
	sudo cp util.h /usr/local/include/util
	sudo cp queue/queue.h /usr/local/include/util
	sudo cp ar_list/ar_list.h /usr/local/include/util

libutil.a: $(OBJ)
	ar rcs $@ $^
	rm *.o

$(OBJ): $(SRC)
	gcc -c $^


