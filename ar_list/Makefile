
BINS=libar_list.a test atest debug
all:  $(BINS)

test: ar_list_test.o ar_list.o
	gcc -o test ar_list.c ar_list_test.c

ar_list.o: ar_list.c ar_list.h
	gcc -c ar_list.o ar_list.c


ar_list_test.o : ar_list.c ar_list_test.c
	gcc -c ar_list_test.o ar_list_test.c ar_list.c

clean:
	rm *.o *.a test atest

debug:
	gcc ar_list_test.c ar_list.c -g

libar_list.a: ar_list.o
	ar rcs libar_list.a ar_list.o

atest: ar_list_test.c
	gcc -o $@ $^ -L. -lar_list

deploy:
	cp ar_list.h /home/maximhrunenko/.local/share/nvim/mason/packages/clangd/clangd_16.0.2/lib/clang/16/include/
	sudo cp libar_list.a /usr/lib/
	sudo cp ar_list.h /usr/include/
