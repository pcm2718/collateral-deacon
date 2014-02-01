#include "buddhaplot.hpp"



/*
 * Might replace this function with overloaded parenthesis.
 */
void
Buddhaplot::update_histograms (long const point_count)
{
  // May add some code here to split up point generation and plotting into chunks.
  // Checkpoints would be written after each chunk of 100000 tests.

  for ( long i = point_count ; i > 0 ; i -= 100000)
    {
      //hack
      auto points = pointgen.get_points (std::min (100000l, i));
      for ( auto & histogram : histograms )
        histogram.ins_pts (points);

      // Checkpoint write here.
    }
};
