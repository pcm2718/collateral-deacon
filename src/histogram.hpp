#include <complex>
#include <vector>
#include <istream>
#include <ostream>



// This may be incorrect usage.
using Resolution = std::pair<long, long>;
using Range = std::pair<std::complex<double>, std::complex<double>>;



class Histogram
{
public:

  /*
   * Public Methods
   */

  Histogram (
             Resolution const & resolution,
             Range const & range ) :
        RESOLUTION (resolution),
        RANGE (range),
        DELTA
        (
           std::pair<double, double>
             (
               ((std::real (range.second) - std::real (range.first)) / resolution.first),
               ((std::imag (range.second) - std::imag (range.first)) / resolution.second)
             )
        ),
        max_cell (0),
        histogram (std::vector<long> (resolution.first * resolution.second, 0))
  {
  }



  friend std::ostream &
  operator<< (std::ostream & ost, Histogram const & plot);


  friend std::istream &
  operator>> (std::istream & ist, Histogram & plot);



  friend std::ostream &
  operator<< (std::stringstream & ost, Histogram const & plot);



  friend std::istream &
  operator>> (std::stringstream & ist, Histogram & plot);



  void
  clear ();



  long
  get_at (long const x, long const y) const;



  /*
  Cell const &
  inc_at (long const x, long const y);



  Cell const &
  dec_at (long const x, long const y);



  Cell const &
  ins_pt (std::complex<double> const & point);
  */



  void
  ins_pts (std::vector<std::complex<double>> const & points);



  /*
   * Public Variables
   */

  Resolution const RESOLUTION;

  Range const RANGE;

  std::pair<double, double> const DELTA;



private:

  /*
   * Private Methods
   */

  std::string
  get_color (long const score) const;



  /*
   * Private Variables
   */

  long max_cell;

  std::vector<long> histogram;
};
