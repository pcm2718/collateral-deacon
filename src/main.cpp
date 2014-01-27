#include <iostream>
/*
 * Add ifndef later.
 */
//#include "mandelbrot.hpp"
#include "buddhaplot.hpp"



int
main (int argc, char **argv)
{
  auto buddhaplot = Buddhaplot (std::pair<long, long>(350, 200),
				std::pair<std::complex<double>,	std::complex<double>> (std::complex<double>(-2.5, -1), std::complex<double>(1, 1)),
				1000);

  buddhaplot.generate_histogram (1000, 1);

  std::cout << buddhaplot << std::endl;

  return 0;
};
