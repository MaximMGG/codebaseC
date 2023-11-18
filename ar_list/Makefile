test: ar_list_test.o ar_list.o
	gcc -o test ar_list.c ar_list_test.c

ar_list.o: ar_list.c
	gcc -c ar_list.o ar_list.c

ar_list_test.o : ar_list.c ar_list_test.c
	gcc -c ar_list_test.o ar_list_test.c ar_list.c

clean:
	rm *.o test
