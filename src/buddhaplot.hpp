#include <complex>
#include <vector>
#include <string>
#include <ostream>
#include <iostream>



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
    RESOLUTION (resolution), RANGE (range), MAX_ITTR (max_ittr),
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

  long const MAX_ITTR;



private:

  /*
   * Private Methods
   */

  std::vector<std::complex<double>>
  generate_trajectory (std::complex<double> const & cval) const;



  std::vector<std::complex<double>>
  get_points (long const test_count);



  /*
   * I may have to adjust this function to copy, update, and then reassign the histogram vector.
   */
  void
  update_histogram (std::vector<std::complex<double>> const & points);



  std::string
  get_color (long const score) const;



  /*
   * Private Variables
   */

  long max_cell;

  Histogram<long> histogram;
};
