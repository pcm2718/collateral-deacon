#include "buddhaplot.hpp"


/*
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
*/



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
  
  std::cout << "PID " << NODE << " updating histograms." << std::endl;

  for ( long i = point_count ; i > 0 ; i -= CHUNK_SIZE)
    {
      auto const points = pointgen.get_points (std::min (CHUNK_SIZE, i));
      for ( unsigned long j = 0 ; histograms.size () ; ++j )
        {
          /*
           * Add the new points to histogram.
           */
          histograms[j].ins_pts (points);

          std::cout << "PID " << NODE << " placed points on an instance of histogram " << j << "." << std::endl;

          /*
           * Generate a string representation of histogram.
           */
          std::stringstream ss;
          ss << histograms[j];
          auto histogram_c_len = ss.str ().size ();
          char * histogram_c_str = new char [histogram_c_len];
          strcpy (histogram_c_str, ss.str ().c_str ());

          /*
           * Send the length of the c string and the string itself back to PID 0 for concatenation.
           */
          MPI_Send(&j, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
          MPI_Send(&histogram_c_len, 1, MPI_LONG, 0, 0, MPI_COMM_WORLD);
          MPI_Send(histogram_c_str, histogram_c_len, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

          delete histogram_c_str;

          std::cout << "PID " << NODE << " transmitted an instance of histogram " << j << "." << std::endl;

          /*
           * Clear histogram.
           */
          histograms[j].clear ();
        }
        std::cout << "PID " << NODE << " finished chunk." << std::endl;
    }
};
