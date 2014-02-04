#include "buddhaplot.hpp"



std::ostream &
operator<< (std::ostream & ost, Buddhaplot const &)
{
};



std::istream &
operator<< (std::istream & ist, Buddhaplot &)
{
};



std::ostream &
operator<< (std::fstream & ost, Buddhaplot const &)
{
};



std::istream &
operator<< (std::fstream & ist, Buddhaplot &)
{
};



/*
std::ostream &
operator<< (std::ostream & ost, Buddhaplot const & plot)
{
  //ost << "Buddhabrot Dump File" << std::endl << std::endl << std::endl;

  for ( int i = 0 ; i < histograms.size() ; ++i )
    {
      ost << i << std::endl << histograms[i] << std::endl;
    }
};



std::istream &
operator<< (std::istream & ist, Buddhaplot & plot)
{
};
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
      for ( int j = 0 ; j < histograms.size() ; ++j )
        {
          /*
           * Add the new points to histogram.
           */
          histograms[j].ins_pts (points);

          /*
           * Generate a string representation of histogram.
           */
          std::stringstream ss;
          ss << j << std::endl;
          ss << histograms[j];
          auto histogram_str = std::string (ss.str ());

          /*
           * Send c string of histogram back to PID 0 for concatenation.
           */
          MPI::Comm::Send(histogram_str.c_str (), histogram_str.size (), MPI::CHAR, 0, 0, MPI::COMM_WORLD);

          /*
           * Clear histogram.
           */
          histogram.clear ();
        }
    }
};
