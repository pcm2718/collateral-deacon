all: obj/main.o obj/mandelbrot.o obj/buddhaplot.o
	clang++ -std=c++11 obj/main.o -o bin/collateral-deacon

obj/main.o: src/main.cpp
	clang++ -std=c++11 -I src -c src/main.cpp -o obj/main.o

obj/mandelbrot.o: src/mandelbrot.cpp src/mandelbrot.hpp
	clang++ -std=c++11 -I src -c src/mandelbrot.cpp -o obj/mandelbrot.o

obj/buddhaplot.o: src/buddhaplot.cpp src/buddhaplot.hpp
	clang++ -std=c++11 -I src -c src/buddhaplot.cpp -o obj/buddhaplot.o

clean:
	rm -rf obj/*.o
	rm bin/collateral-deacon
