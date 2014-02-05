#include <iostream>
#include <fstream>
#include "mpi.h"
/*
 * Add ifndef later.
 */
#include "buddhaplot.hpp"



Buddhaplot
get_buddhaplot (int node);



int
main (int argc, char* argv[])
{
  /*
   * Initialize MPI
   */
  MPI::Init (argc, argv);

  // Process Count and Process ID
  int ps_count = MPI::COMM_WORLD.Get_size ();
  int ps_id = MPI::COMM_WORLD.Get_rank ();

  // Wall Time
  double wall_time = 0;

  // Total Time, currently 60 seconds;
  long total_time = 240;

  // Total Point Count, currently 1,000,000,000.
  long total_c_count = 1000000000;

  /*
   * Get buddaplot object.
   * */
  auto buddhaplot = get_buddhaplot (ps_id);


  /*
   * If the process ID is 0, get the wall_time and then start up a structure to accumulate histograms.
   * Accumulate histograms until all other processes are finished.
   * As this block is currently implemented, merges are done after all other processes are done.
   */
  if (ps_id == 0)
    {
      wall_time = MPI::Wtime ();

      int node = 1;
      bool* nodes = new bool[ps_count];

      for ( int i = 1 ; i < ps_count ; ++i)
        nodes[i] = true;


      while (((MPI::Wtime () - wall_time) + 15) < total_time)
        {
          if (! nodes[node])
            continue;
      
          std::stringstream big_laundry;

          /*
           * Recive the next histogram string.
           */

          long hist_index = 0;
          MPI_Recv (&hist_index, 1, MPI_LONG, node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          long str_size = 0;
          MPI_Recv (&str_size, 1, MPI_LONG, node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          char * c_str = new char[str_size];
          MPI_Recv (c_str, str_size, MPI_CHAR, node, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          big_laundry << c_str;
          delete c_str;

          std::cout << "PID 0 got an instance of histogram " << hist_index << " of size " << str_size << " from node " << node << "." << std::endl;

          /*
           * Merge the string into the local histogram.
           */
          big_laundry >> buddhaplot.histograms[hist_index];

          /*
           * Update the node number.
           */
          ++node;
          if (node == ps_count)
            node = 1;
        }

      //delete nodes;

      /*
       * Write images to image files.
       */
      for ( unsigned long i = 0 ; i < buddhaplot.histograms.size () ; ++i )
        {
          std::stringstream filename;
          filename << "tmp/img_" << i << ".ppm";
          std::ofstream fileout (filename.str (), std::ofstream::out|std::ofstream::trunc);
          fileout << buddhaplot.histograms[i] << std::endl;
          fileout.close ();
        }
   }

  /*
   * Otherwise run the actual tests on C values, the number of which
   * is computed to distribute the load as evenly as possible.
   */
  else
    {
      long c_count = (total_c_count / (ps_count-1) ) + ( (ps_id == 1) && (total_c_count % (ps_count-1) != 0) ? 1 : 0 );
      std::cout << "PID " << ps_id << " now testing " << c_count << "C values." << std::endl;
      buddhaplot.update_histograms (c_count);
      std::cout << "PID " << ps_id << " finished testing " << c_count << "C values." << std::endl;
    }


  /*
   * If the process ID is 0, compute and print the elapsed wall time.
   */
  if (ps_id == 0)
    {
      wall_time = MPI::Wtime () - wall_time;
      std::cout << "PID " << ps_id << " elapsed wall time: " << wall_time << std::endl;
    }


  /*
   * Terminate MPI
   */
  MPI::Finalize ();

  return 0;
};



/*
 * This function just sets up the buddhaplot object that will be used by each PID.
 */
Buddhaplot
get_buddhaplot (int node)
{
  /*
   * Define our domain for sample c values and max_ittr for plotgen.
   */
  auto c_domain = std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.25, -1.5), std::complex<double> (0.75, 1.5));
  auto max_ittr = 400;

  /*
   * Define our lists of histogram settings.
   */
  auto resolutions = std::vector<std::pair<long, long>>
    {std::pair<long, long> (1920, 1920)};
//      std::pair<long, long> (640, 640)};

  auto ranges = std::vector<std::pair<std::complex<double>, std::complex<double>>>
    {std::pair<std::complex<double>, std::complex<double>> (std::complex<double> (-2.25, -1.5), std::complex<double> (0.75, 1.5))};
//    std::pair<std::complex<double>, std::complex<double>> (std::complex<double> (-1, -1), std::complex<double> (1, 1))};

  /*
   * Define buddhaplot object.
   */
  return Buddhaplot (node, c_domain, max_ittr, resolutions, ranges);
};
