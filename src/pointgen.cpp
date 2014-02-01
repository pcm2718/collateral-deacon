#include "pointgen.hpp"



std::vector<std::complex<double>>
Pointgen::get_points (long const point_count) const
{
  // May want to move random init to class constructor.
  std::random_device rd;
  std::mt19937 rng = std::mt19937 (rd());
  auto real_dist = std::uniform_real_distribution<double> (std::real (C_DOMAIN.first), std::real (C_DOMAIN.second));
  auto imag_dist = std::uniform_real_distribution<double> (std::imag (C_DOMAIN.first), std::imag (C_DOMAIN.second));

  auto points = std::vector<std::complex<double>> ();

  /*
   * Note that it is possible, if extremely unlikely, for this loop to be non-terminating.
   */
  for ( int i = 0 ; i < point_count ; )
    {
      auto trajectory = generate_trajectory (std::complex<double> (real_dist (rng), imag_dist (rng)));

      // May be faster with an if statement to ignore empty trajectories.
      points.insert (points.end(), trajectory.begin(), trajectory.end());
      //i += trajectory.size ();
      ++i;
    }

  return points;
};



/*
 * This function needs to be checked for correctness.
 */
std::vector<std::complex<double>>
Pointgen::generate_trajectory(std::complex<double> const & cval) const
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
