#include "pointgen.hpp"



std::vector<std::complex<double>>
Pointgen::get_points (long const c_count)
{
  auto points = std::vector<std::complex<double>> ();

  /*
   * Note that it is possible, if extremely unlikely, for this loop to be non-terminating.
   */
  for ( long i = 0 ; i < c_count ; )
    {
      auto trajectory = generate_trajectory (std::complex<double> (real_dist (rng), imag_dist (rng)));

      if (!trajectory.empty ())
        points.insert (points.end (), trajectory.begin (), trajectory.end ());

      i += trajectory.size ();
      //++i
    }

  return points;
};



/*
 * This function needs to be checked for correctness.
 */
std::vector<std::complex<double>>
Pointgen::generate_trajectory(std::complex<double> const & c_val) const
{
  auto trajectory = std::vector<std::complex<double>> ();
  auto z_val = std::complex<double> (0, 0);

  bool escaped = false;
 
  for ( long n = 0 ; n < MAX_ITTR ; ++n )
    {
      if (std::abs (z_val) > 2)
        escaped = true;

      z_val = std::pow (z_val, 2) + c_val;
      trajectory.push_back (z_val);
    }
   
  if (!escaped)
    trajectory.clear();

  return trajectory;
};
