#include <iostream>
#include <fstream>
/*
 * Add ifndef later.
 */
#include "buddhaplot.hpp"



int
main ()
{
  /*
   * Define buddhaplot object.
   */
  auto buddhaplot = Buddhaplot (std::pair<long, long> (1024, 768),
                                std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.5, -1), std::complex<double> (1, 1)),
                                std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.5, -1), std::complex<double> (1, 1)),
                                //std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-0.5, -1.3), std::complex<double> (2, 1.3)),
                                100);

  /*
   * Test 1,000,000 points.
   */
  buddhaplot.generate_histogram (1000000, 1);

  /*
   * Write image to image file.
   */
  std::ofstream fileout ("tmp/feh_tmp.ppm", std::ofstream::out|std::ofstream::trunc);
  fileout << buddhaplot << std::endl;
  fileout.close();

  return 0;
}
