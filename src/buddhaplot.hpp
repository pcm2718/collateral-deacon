#include <complex>
#include <vector>
#include <string>
#include <ostream>



//class Buddhaplot;
//std::ostream &
//operator<< (std::ostream &, Buddhaplot const &);



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
	      std::pair<std::complex<double>, std::complex<double>> const & range, long const & max_ittr) : 
    RESOLUTION (resolution), RANGE (range), MAX_ITTR (max_ittr),
    DELTA (std::pair<double, double> ((std::real(range.second) - std::real(range.first) / resolution.first), (std::imag(range.second) - std::imag(range.first) / resolution.second))),
    histogram (std::vector<std::vector<long>> (resolution.first, std::vector<long> (resolution.second, 0)))
      {
      };



  friend std::ostream &
  operator<< (std::ostream &, Buddhaplot const &);



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

  std::string
  get_color (long const & score) const;



  /*
   * Private Variables
   */

  Histogram<long> histogram;
};
