#include <iostream>
#include <fstream>
#include "mpi.h"
/*
 * Add ifndef later.
 */
#include "buddhaplot.hpp"



int
main (int argc, char* argv[])
{
  // Total Point Count, currently 1,000,000,000.
  long total_points = 1000000000;

  // Process Count
  int ps_count = 0;

  // Process ID
  int ps_id = 0;

  // Wall Time
  double wall_time = 0;

  /*
   * Initialize MPI
   */
  MPI::Init (argc, argv);

  /*
   * Get the number of processes.
   */
  ps_count = MPI::COMM_WORLD.Get_size ();

  /*
   * Get the process ID.
   */
  ps_id = MPI::COMM_WORLD.Get_rank ();


  /*
   * If the process ID is 0, get the wall_time and then start up a structure to accumulate histograms.
   * Accumulate histograms until all other processes are finished.
   */
  if (ps_id == 0)
    {
      wall_time = MPI::Wtime ();

      // Checkpoint write here.

    }
  /*
   * Otherwise, recieve orders from process 0 to start with computations.
   */
  else
    {
      // Remove this line later.
      wall_time = MPI::Wtime ();

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
      auto buddhaplot = Buddhaplot (c_domain, max_ittr, resolutions, ranges);

      /*
       * Compute the number of points to test per PID. HACK.
       */
      long points = (total_points / (ps_count-1) ) + 1;

      /*
       * Run actual tests. Change this comment later.
       */
      buddhaplot.update_histograms (points);

      /*
       * Write image to image file.
       */
      std::ofstream fileout ("tmp/mpi_" + std::to_string(ps_id) + ".ppm", std::ofstream::out|std::ofstream::trunc);
      fileout << buddhaplot.histograms[0] << std::endl;
      fileout.close ();
    }


  /*
   * If the process ID is 0, compute and print the elapsed wall time.
   */
  if (ps_id != 0)
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
