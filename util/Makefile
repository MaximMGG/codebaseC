

lib_util.a: queue.o ar_list.o
	ar rcs $@ $^

queue.o: queue/queue.c
	gcc -c $< -o $@ -g

ar_list.o: ar_list/ar_list.c
	gcc -c $< -o $@ -g

deploy:
	sudo mkdir -p /usr/local/include/util
	sudo cp ar_list/ar_list.h /usr/local/include/util/
	sudo cp queue/queue.h /usr/local/include/util/
	sudo cp util.h /usr/local/include/util/
	sudo cp lib_util.a /usr/local/lib/
	cp *.o obj/
