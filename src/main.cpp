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
   * Define our domain for sample c values and max_ittr for plotgen.
   */
  auto c_domain = std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.25, -1.5), std::complex<double> (0.75, 1.5));
  auto max_ittr = 400;

  /*
   * Define our lists of histogram settings.
   */
  //auto resolutions = std::vector<std::pair<long, long> > () {std::pair<long, long> (1024, 768)};
  //auto ranges = std::vector<std::pair<std::complex<double>, std::complex<double> > > () {std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.5, -1), std::complex<double> (1, 1))};
  auto resolutions = std::vector<std::pair<long, long> > (1, std::pair<long, long> (640, 640));
  auto ranges = std::vector<std::pair<std::complex<double>, std::complex<double> > > (1, std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.25, -1.5), std::complex<double> (0.75, 1.5)));

  /*
   * Define buddhaplot object.
   */
  /*
  auto buddhaplot = Buddhaplot (std::pair<long, long> (1024, 768),
                                std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.5, -1), std::complex<double> (1, 1)),
                                std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.5, -1), std::complex<double> (1, 1)),
                                //std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-0.5, -1.3), std::complex<double> (2, 1.3)),
                                100);
                                */
  auto buddhaplot = Buddhaplot (c_domain, max_ittr, resolutions, ranges);


  /*
   * Test 10,000,000 points.
   */
  buddhaplot.update_histograms (1000000);

  /*
   * Write image to image file.
   */
  std::ofstream fileout ("tmp/feh_tmp.ppm", std::ofstream::out|std::ofstream::trunc);
  fileout << buddhaplot.histograms[0] << std::endl;
  fileout.close();

  return 0;
}
