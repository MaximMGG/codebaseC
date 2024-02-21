LIB = lib_util.a
SRC = ar_list/m_list.c pr_map/pr_map.c queue/queue.c str/m_string.c linked_list/m_linkedlist.c
OBJ = $(patsubst %.c, %.o, $(SRC))

all = $(LIB)
 
$(LIB): $(OBJ) 
	ar rcs $@ $^

# $(OBJ): ar_list/ar_list.c pr_map/pr_map.c queue/queue.c
# 	gcc -o $@ -c $< -g

# m_list.o:
# 	gcc -o $@ -c ar_list/m_list.c -g
#
# pr_map.o:
# 	gcc -o $@ -c pr_map/pr_map.c -g
#
# queue.o:
# 	gcc -o $@ -c queue/queue.c -g
#
# m_string.o:
# 	gcc -o $@ -c str/m_string.c -g

%.o: %.c
	gcc -o $@ -c $< -g

clean:
	rm *.a $(OBJ)

deploy:
	sudo cp $(LIB) /usr/lib/
	sudo mkdir -p /usr/include/util
	sudo cp ar_list/m_list.h /usr/include/util/
	sudo cp pr_map/pr_map.h /usr/include/util/
	sudo cp queue/queue.h /usr/include/util/
	sudo cp str/m_string.h /usr/include/util/
	sudo cp	linked_list/m_linkedlist.h /usr/include/util/
	sudo cp	util.h /usr/include/util
