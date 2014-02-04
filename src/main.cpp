#include <iostream>
#include <fstream>
#include "mpi.h"
/*
 * Add ifndef later.
 */
#include "buddhaplot.hpp"



Buddhaplot
get_buddhaplot ();



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

  // Total Point Count, currently 1,000,000,000.
  long total_c_count = 1000000000;

  /*
   * Get buddaplot object.
   * */
  auto buddhaplot = get_buddhaplot ();


  /*
   * If the process ID is 0, get the wall_time and then start up a structure to accumulate histograms.
   * Accumulate histograms until all other processes are finished.
   * As this block is currently implemented, merges are done after all other processes are done.
   */
  if (ps_id == 0)
    {
      wall_time = MPI::Wtime ();

      std::stringstream big_laundry;

      while (true)
        {
          /*
           * Recive the next histogram string.
           */
          //std::stringstream ss = ;


          /*
           * Here, figure out how to distinguish between histograms.
           * Easy, use an index.
           */
          



          /*
           * Merge the string into the local histogram.
           */
          //buddhaplot.histograms[0] << ss;

          // Checkpoint write here.
          //
          // Remember to set up early terminate in the event the job is axed.
        }

      std::cout << buddhaplot;

      /*
       * Write image to image file.
       */
      std::ofstream fileout ("tmp/img_0.ppm", std::ofstream::out|std::ofstream::trunc);
      fileout << buddhaplot.histograms[0] << std::endl;
      fileout.close ();
   }

  /*
   * Otherwise run the actual tests on C values, the number of which
   * is computed to distribute the load as evenly as possible.
   */
  else
    {
      long c_count = (total_c_count / (ps_count-1) ) + ( (ps_id == 1) ? 1 : 0 );
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
get_buddhaplot ()
{
  /*
   * Define our domain for sample c values and max_ittr for plotgen.
   */
  auto c_domain = std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.25, -1.5), std::complex<double> (0.75, 1.5));
  auto max_ittr = 400;

  /*
   * Define our lists of histogram settings.
   */
  auto resolutions = std::vector<std::pair<long, long> > (1, std::pair<long, long> (1920, 1920));
  auto ranges = std::vector<std::pair<std::complex<double>, std::complex<double> > > (1, std::pair<std::complex<double>, std::complex<double> > (std::complex<double> (-2.25, -1.5), std::complex<double> (0.75, 1.5)));

  /*
   * Define buddhaplot object.
   */
  return Buddhaplot (c_domain, max_ittr, resolutions, ranges);
};
