export OMPI_CC=clang
export OMPI_CXX=clang++

MPI_CXX="mpic++"

all: obj/main.o obj/buddhaplot.o obj/pointgen.o obj/histogram.o
	$(MPI_CXX) -std=c++11 -L obj obj/pointgen.o obj/histogram.o obj/buddhaplot.o obj/main.o -o bin/collateral-deacon

obj/main.o: src/main.cpp src/buddhaplot.hpp src/pointgen.hpp src/histogram.hpp
	$(MPI_CXX) -g -Wall -Wextra -Werror -std=c++11 -I src -c src/main.cpp -o obj/main.o

obj/buddhaplot.o: src/buddhaplot.cpp src/buddhaplot.hpp src/pointgen.hpp src/histogram.hpp
	$(MPI_CXX) -g -Wall -Wextra -Werror -std=c++11 -I src -c src/buddhaplot.cpp -o obj/buddhaplot.o

obj/pointgen.o: src/pointgen.cpp src/pointgen.hpp
	$(MPI_CXX) -g -Wall -Wextra -Werror -std=c++11 -I src -c src/pointgen.cpp -o obj/pointgen.o

obj/histogram.o: src/histogram.cpp src/histogram.hpp
	$(MPI_CXX) -g -Wall -Wextra -Werror -std=c++11 -I src -c src/histogram.cpp -o obj/histogram.o

clean:
	rm -rf obj/*.o
	rm bin/collateral-deacon
