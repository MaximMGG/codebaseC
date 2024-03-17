



test: test.o
	gcc -o $@ $^ $(OBJ) -g -l_util -lassert

test.o: main.c 
	gcc -o $@ -c $< -g 

clean:
	rm test.o ./test
