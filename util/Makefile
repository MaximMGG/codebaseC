LIB = lib_util.a
SRC = ar_list/ar_list.c pr_map/pr_map.c queue/queue.c
OBJ = ar_list.o pr_map.o queue.o

all = ar_list.o pr_map.o queue.o $(LIB)
 
$(LIB): $(OBJ) 
	ar rcs $@ $^ 

# $(OBJ): ar_list/ar_list.c pr_map/pr_map.c queue/queue.c
# 	gcc -o $@ -c $< -g

ar_list.o:
	gcc -o $@ -c ar_list/ar_list.c -g

pr_map.o:
	gcc -o $@ -c pr_map/pr_map.c -g

queue.o:
	gcc -o $@ -c queue/queue.c -g


clean:
	rm *.a *.o

deploy:
	sudo cp $(LIB) /usr/lib/
	sudo mkdir -p /usr/include/util
	sudo cp ar_list/ar_list.h /usr/include/util/
	sudo cp pr_map/pr_map.h /usr/include/util/
	sudo cp queue/queue.h /usr/include/util/
	sudo cp	util.h /usr/include/util
