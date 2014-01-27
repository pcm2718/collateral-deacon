all: obj/main.o obj/mandelbrot.o obj/buddhaplot.o
	clang++ -std=c++11 -L obj obj/buddhaplot.o obj/main.o -o bin/collateral-deacon

obj/main.o: src/main.cpp
	clang++ -g -std=c++11 -I src -c src/main.cpp -o obj/main.o

obj/buddhaplot.o: src/buddhaplot.cpp src/buddhaplot.hpp
	clang++ -g -std=c++11 -I src -c src/buddhaplot.cpp -o obj/buddhaplot.o

clean:
	rm -rf obj/*.o
	rm bin/collateral-deacon
