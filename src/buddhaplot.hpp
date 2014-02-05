#include <complex>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include "mpi.h"

#include "pointgen.hpp"
#include "histogram.hpp"



class Buddhaplot
{
public:

  /*
   * Public Methods
   */

  Buddhaplot (
              int node,
              CDomain const & c_domain,
              long const max_ittr,
              std::vector<Resolution> const & resolutions,
              std::vector<Range> const & ranges ) :
    NODE (node),
    RESOLUTIONS (resolutions),
    RANGES (ranges),
    CHUNK_SIZE (10000),
    pointgen (c_domain, max_ittr),
    histograms ()
  {
    /*
     * Find a way to do this in the initializer if at all possible.
     * May replace vector with some sort of set.
     * This is a hack.
     */
    for ( unsigned long i = 0 ; i < resolutions.size () ; ++i )
      histograms.push_back (Histogram (resolutions[i], ranges[i]));
  }



  friend std::ostream &
  operator<< (std::ostream &, Buddhaplot const &);



  friend std::istream &
  operator<< (std::istream &, Buddhaplot &);



  friend std::ostream &
  operator<< (std::fstream &, Buddhaplot const &);



  friend std::istream &
  operator<< (std::fstream &, Buddhaplot &);


  void
  update_histograms (long const point_count);



  /*
   * Public Variables
   */

  int const NODE;

  std::vector<std::pair<long, long>> const RESOLUTIONS;

  std::vector<std::pair<std::complex<double>, std::complex<double>>> const RANGES;

  long const CHUNK_SIZE;



//private:

  /*
   * Private Variables
   */

  Pointgen pointgen;

  std::vector<Histogram> histograms;
};
