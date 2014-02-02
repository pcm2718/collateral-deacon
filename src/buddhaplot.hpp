#include <complex>
#include <string>
#include <vector>
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
              CDomain const & c_domain,
              long const max_ittr,
              std::vector<Resolution> const & resolutions,
              std::vector<Range> const & ranges ) : 
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



  void
  update_histograms (long const point_count);



  /*
   * Public Variables
   */

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
