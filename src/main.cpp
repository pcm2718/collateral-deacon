#include <iostream>
#include "mandelbrot.hpp"
#include "buddhaplot.hpp"



int
main (int argc, char** argv)
{
  auto mandelbrot = Mandelbrot (1000);

  auto buddhaplot = Buddhaplot (std::pair<long, long> (10, 10),
				std::pair<std::complex<double>, std::complex<double>> (std::complex<double> (-5, -5), std::complex<double> (5, 5)),
				1000);

  std::cout << buddhaplot << std::endl;

  return 0;
};
