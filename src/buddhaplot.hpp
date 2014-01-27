#include <complex>
#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include "mandelbrot.hpp"



// This code sort of iffy.
template <class T>
using Histogram = std::vector<std::vector<T>>;



class Buddhaplot
{
public:

  /*
   * Public Methods
   */

  Buddhaplot (std::pair<long, long> const & resolution,
	      std::pair<std::complex<double>, std::complex<double>> const & range, long const max_ittr) : 
    RESOLUTION (resolution), RANGE (range), mandelbrot (Mandelbrot (max_ittr)),
    DELTA
      (
	   std::pair<double, double>
	     (
	       (std::real(range.second) - std::real(range.first) / resolution.first),
	       (std::imag(range.second) - std::imag(range.first) / resolution.second)
	     )
      ),
    max_cell (0),
    histogram (std::vector<std::vector<long>> (resolution.first, std::vector<long> (resolution.second, 0)))
    {
    };



  friend std::ostream &
  operator<< (std::ostream &, Buddhaplot const &);



  void
  generate_histogram (long const test_count, long const node_count);



  /*
   * Public Variables
   */

  std::pair<long, long> const RESOLUTION;

  std::pair<std::complex<double>, std::complex<double>> const RANGE;

  std::pair<double, double> const DELTA;

  Mandelbrot mandelbrot;



private:

  /*
   * Private Methods
   */

  std::string
  get_color (long const score) const;



  std::vector<std::complex<double>>
  generate_trajectories (long const test_count);



  /*
   * I may have to adjust this function to copy, update, and then reassign the histogram vector.
   */
  void
  update_histogram (std::vector<std::complex<double>> const & points);




  /*
   * Private Variables
   */

  long max_cell;

  Histogram<long> histogram;
};
