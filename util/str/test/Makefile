



test: test.o m_string.o
	gcc -o $@ $^ $(OBJ) -g -l_util -lassert

m_string.o: ../m_string.c
	gcc -o $@ -c $< -g

test.o: main.c 
	gcc -o $@ -c $< -g 

clean:
	rm test.o ./test
