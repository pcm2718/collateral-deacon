#include <istream>
#include <ostream>



template<class Cell>
class Histogram
{
public:

  /*
   * Public Methods
   */

  Histogram (std::pair<long, long> const & resolution,
             std::pair<std::complex<double>, std::complex<double>> const & range,
             Cell init) :
        RESOLUTION (resolution),
        RANGE (range),
        max_cell (init),
        histogram (std::vector<Cell> (resolution.first * resolution.second, init)
  {
  }



  Cell const &
  get_at (long const x, long const y) const;



  Cell const &
  inc_at (long const x, long const y);



  Cell const &
  dec_at (long const x, long const y);



  Cell const &
  ins_pt (std::complex<double> const & point);



  void
  ins_pts (std::vector<std::complex<double>> const & points);



  friend ostream &
  operator<< (ostream & ost, Histogram const & histogram);



  friend istream &
  operator>> (istream & ist, Histogram & histogram);



  /*
   * Public Variables
   */

  std::pair<long, long> const RESOLUTION;

  std::pair<std::complex<double>, std::complex<double>> const  RANGE;



private:

  /*
   * Private Variables
   */

  Cell max_cell;

  std::vector<Cell> histogram;
};
