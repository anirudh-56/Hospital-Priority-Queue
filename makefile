test:
	rm -f tests.exe
	g++ -Wall -std=c++20 tests.cpp -o tests.exe

runtest:
	./tests.exe

clean:
	rm -f tests.exe

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes  ./tests.exe
