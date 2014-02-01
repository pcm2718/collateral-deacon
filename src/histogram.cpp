#include "histogram.hpp"


std::ostream &
operator<< (std::ostream & ost, Histogram const & plot)
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
          ost << plot.get_color (plot.histogram[j * plot.RESOLUTION.first + i]) << " ";
        }
      ost << std::endl;
    }

  /*
   * Return the outstream.
   */
  return ost;
};



long
Histogram::get_at (long const x, long const y) const
{
  return histogram[y*RESOLUTION.first + x];
};



void
Histogram::ins_pts (std::vector<std::complex<double>> const & points)
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

      ++histogram[y*RESOLUTION.first + x];
    }

  /*
   * Find the cell with the most points, record the value in max_cell.
   * There may be a better way to do this through the std:: libraries (maybe std::max).
   */
  long max = 0;
  for ( unsigned long i = 0 ; i < histogram.size () ; ++i )
    if ( histogram[i] > max )
      max = histogram[i];
  max_cell = max;
};



std::string
Histogram::get_color (long const score) const
{
  std::ostringstream convert;

  if (max_cell != 0)
    convert << static_cast<long> ( 255 * (static_cast<double> (score) / max_cell) );

  return convert.str();
};
