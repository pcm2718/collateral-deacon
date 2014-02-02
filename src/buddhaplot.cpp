#include "buddhaplot.hpp"



/*
 * Might replace this function with overloaded parenthesis.
 */
void
Buddhaplot::update_histograms (long const point_count)
{
  // May add some code here to split up point generation and plotting into chunks.
  // Checkpoints would be written after each chunk of tests.

  for ( long i = point_count ; i > 0 ; i -= CHUNK_SIZE)
    {
      //hack
      auto points = pointgen.get_points (std::min (CHUNK_SIZE, i));
      for ( auto & histogram : histograms )
        {
          /*
           * Add the new points to histogram.
           */
          histogram.ins_pts (points);

          /*
           * Generate a string representation of histogram.
           */
          //std::stringstream ss;
          //ss << histogram;
          //auto histogram_str = std::string (ss.str ());

          //std::cout << "Histogram String Example: " << histogram << std::endl << std::endl;

          /*
           * Send c string of histogram back to PID 0 for concatenation.
           */
          //MPI::Comm::Send(histogram_str.c_str (), histogram_str.size (), MPI::CHAR, 0, 0, MPI::COMM_WORLD);

          /*
           * Clear histogram.
           */
          //histogram.clear ();
        }
    }
};
