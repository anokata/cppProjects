build: hello libHello.so

run: 
	LD_LIBRARY_PATH=. ./hello

hello: main.c hello.h libHello.so solution.c
	gcc main.c solution.c -fPIC -L. -lHello -o hello

libHello.so: hello.h hello.c
	gcc -shared hello.c -fPIC -o libHello.so

libSolution.so: solution.c
	gcc -shared solution.c -fPIC -o libSolution.so

clean:
	-rm *.o 2>/dev/null
	-rm hello 2>/dev/null
	-rm libHello.so 2>/dev/null
	
