#include "buddhaplot.hpp"
#include <algorithm>
#include <chrono>
#include <random>



std::ostream &
operator<< (std::ostream & ost, Buddhaplot const & plot)
{
  /*
   * Set magic number for filetype. Currently "plain" greymap. Should adjust to binary later.
   */
  ost << "P2" << std::endl;

  /*
   * Set the dimensions line of the file.
   */
  ost << plot.RESOLUTION.first << " " << plot.RESOLUTION.second << std::endl;

  /*
   * Set the maximum grey value file, currently fixed at 255.
   */
  ost << "255" << std::endl;

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
  // Remove this later.
  auto x = node_count;
  x=1;

  update_histogram (get_points (test_count));
};



/*
 * This function needs to be checked for correctness.
 */
std::vector<std::complex<double>>
Buddhaplot::generate_trajectory(std::complex<double> const & cval) const
{
  auto trajectory = std::vector<std::complex<double>> ();
  auto zval = std::complex<double> (0, 0);

  bool escaped = false;
 
  for (long n = 0 ; n < MAX_ITTR ; ++n )
    {
      // This if may be redundant.
      if (std::abs (zval) > 2)
        escaped = true;

      zval = std::pow (zval, 2) + cval;
      trajectory.push_back (zval);
    }
   
  if (escaped)
    return trajectory;
  else
    return std::vector<std::complex<double>> ();
};



std::vector<std::complex<double>>
Buddhaplot::get_points (long const test_count)
{
  std::random_device rd;
  std::mt19937 rng = std::mt19937 (rd());
  auto real_dist = std::uniform_real_distribution<double> (std::real (C_DOMAIN.first), std::real (C_DOMAIN.second));
  auto imag_dist = std::uniform_real_distribution<double> (std::imag (C_DOMAIN.first), std::imag (C_DOMAIN.second));

  auto points = std::vector<std::complex<double>> ();

  for ( int i = 0 ; i < test_count ; ++i )
    {
      auto c_val = std::complex<double> (real_dist (rng), imag_dist (rng));
      auto trajectory = generate_trajectory (c_val);

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
      // There may be a nice complex operator for this.
      if (
          std::real (point) < std::real (RANGE.first) ||
          std::imag (point) < std::imag (RANGE.first) ||
          std::real (point) > std::real (RANGE.second) ||
          std::imag (point) > std::imag (RANGE.second)
         )
        continue;

      /*
       * Might be able to compress this into one complex subtraction and division.
       */
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



std::string
Buddhaplot::get_color (long const score) const
{
  std::ostringstream convert;

  if (max_cell != 0)
    convert << static_cast<long> ( 255 * (static_cast<double> (score) / max_cell) );
  else
    convert << 0;

  return convert.str();
};
