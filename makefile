all: src/main.o src/mandelbrot.o
	clang++ -std=c++11 src/main.o -o bin/collateral-deacon

src/main.o: src/main.cpp
	clang++ -std=c++11 -I src -c src/main.cpp -o src/main.o

src/mandelbrot.o: src/mandelbrot.cpp src/mandelbrot.hpp
	clang++ -std=c++11 -I src -c src/mandelbrot.cpp -o src/mandelbrot.o

clean:
	rm -rf src/*.o
	rm bin/collateral-deacon
