all: obj/main.o obj/buddhaplot.o obj/histogram.o
	clang++ -std=c++11 -L obj obj/buddhaplot.o obj/main.o -o bin/collateral-deacon

obj/main.o: src/main.cpp src/buddhaplot.hpp
	clang++ -g -Wall -Wextra -Werror -std=c++11 -I src -c src/main.cpp -o obj/main.o

obj/buddhaplot.o: src/buddhaplot.cpp src/buddhaplot.hpp src/histogram.hpp
	clang++ -g -Wall -Wextra -Werror -std=c++11 -I src -c src/buddhaplot.cpp -o obj/buddhaplot.o

obj/histogram.o: src/histogram.cpp src/histogram.hpp
	clang++ -g -Wall -Wextra -Werror -std=c++11 -I src -c src/histogram.cpp -o obj/histogram.o

clean:
	rm -rf obj/*.o
	rm bin/collateral-deacon
