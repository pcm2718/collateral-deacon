#include "buddhaplot.hpp"
#include <algorithm>

// Get rid of this later.
#include <random>



std::ostream &
operator<< (std::ostream & ost, Buddhaplot const & plot)
  {
    /*
     * Set magic number for filetype. Currently greymap.
     */
    ost << "P2" << std::endl;

    /*
     * Set the dimensions line of the file.
     */
    ost << plot.RESOLUTION.first << " " << plot.RESOLUTION.second << std::endl;

    /*
     * Set the maximum grey value file, currently fixed at 100.
     */
    ost << "100" << std::endl;

    /*
     * Put the actual greydata into the stream.
     */
    for ( int j = plot.RESOLUTION.second - 1 ; j >= 0 ; --j )
      {
	for ( int i = 0 ; i < plot.RESOLUTION.first ; ++i )
	  {
	    /*
	     * Get the greyvalue, put it and a following space into the stream.
	     */
	    ost << plot.get_color (plot.histogram[i][j]) << " ";
	  }
	ost << std::endl;
      }

    /*
     * Return the outstream.
     */
    return ost;
  };



void
Buddhaplot::generate_histogram (long const test_count, long const node_count)
{
  update_histogram (generate_trajectories (test_count));
};



std::vector<std::complex<double>>
Buddhaplot::generate_trajectories (long const test_count)
{
  auto rng = std::mt19937 ();
  auto real_dist = std::uniform_real_distribution<double> (std::real (RANGE.first), std::real (RANGE.second));
  auto imag_dist = std::uniform_real_distribution<double> (std::imag (RANGE.first), std::imag (RANGE.second));

  auto points = std::vector<std::complex<double>> ();

  for ( int i = 0 ; i < test_count ; ++i )
    {
      auto c_val = std::complex<double> (real_dist (rng), imag_dist (rng));
      auto trajectory = mandelbrot.get_trajectory (c_val);
      points.insert (points.end(), trajectory.begin(), trajectory.end());
    }

  return points;
};



void
Buddhaplot::update_histogram (std::vector<std::complex<double>> const & points)
{
  /*
   * Put each point into a histogram cell.
   */
  for ( auto const & point : points )
    {
      long x = (std::real (point) - std::real (RANGE.first)) / DELTA.first;
      long y = (std::imag (point) - std::imag (RANGE.first)) / DELTA.second;

      ++histogram[x][y];
    }

  /*
   * Find the cell with the most points, record the value in max_cell.
   * There may be a better way to do this through the std:: libraries (maybe std::max).
   */
  long max = 0;
  for ( int i = 0 ; i < RESOLUTION.first ; ++i )
    for ( int j = 0 ; j < RESOLUTION.second ; ++j )
      if ( histogram[i][j] > max )
	max = histogram[i][j];
  max_cell = max;
};



/*
 * Not yet implemented.
 */
/*
std::string
Buddhaplot::get_color (long const score) const
  {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    return std::to_string(dist(rd));
    // return "10";
  };
*/
std::string
Buddhaplot::get_color (long const score) const
  {
    std::ostringstream convert;

    if (max_cell != 0)
      convert << static_cast<long> ( (static_cast<double> (score) * 100) / max_cell );
    else
      convert << 0;

    return convert.str();
  };
