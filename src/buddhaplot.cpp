#include "buddhaplot.hpp"
#include <algorithm>
#include <chrono>
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



/*
 * This function needs to be checked for correctness.
 */
std::vector<std::complex<double>>
Buddhaplot::get_trajectory (std::complex<double> const & cval) const
  {
    auto trajectory = std::vector<std::complex<double>> ();
    auto zval = std::complex<double> (0, 0);
 
    /*
     * May need to add condition to detect escape.
     */
    for (long n = 0 ; n < MAX_ITTR ; ++n )
      {
        trajectory.push_back (zval);
        zval = std::pow (zval, 2) + cval;
      }
    
    if (std::abs (zval) < 2)
      return std::vector<std::complex<double>> ();
    else
      return trajectory;
  };



std::vector<std::complex<double>>
Buddhaplot::get_points (long const test_count)
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  auto rng = std::mt19937 (seed);
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
