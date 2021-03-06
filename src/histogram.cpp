#include "histogram.hpp"



/*
 * This function writes a ppm file based on the histogram to ost.
 */
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



/*
std::istream &
operator>> (std::fstream & ist, Histogram & plot)
{
  auto in = std::string ();

  *
   * Make sure the magic number is "P2".
   *//*
  ist >> in;

  // Add check here.

  *
   * Make sure the file dimensions match the dimensions of plot.
   *//*
  long w, h = 0;
  ist >> w >> h;

  // Add check here.

  *
   * Set the maximum grey value file, currently fixed at 255.
   *//*
  ost << "255" << std::endl;

  *
   * Put the actual greydata into the stream.
   *//*
  for ( int j = plot.RESOLUTION.second - 1 ; j >= 0 ; --j )
    {
      for ( int i = 0 ; i < plot.RESOLUTION.first ; ++i )
        {
          *
           * Get the greyvalue, put it and a following space into the stream.
           *//*
          ost << plot.get_color (plot.histogram[j * plot.RESOLUTION.first + i]) << " ";
        }
      ost << std::endl;
    }

  *
   * Return the outstream.
   *//*
  return ist;
};
*/



std::ostream &
operator<< (std::stringstream & ost, Histogram const & plot)
{
  /*
   * Write the dimensions line.
   */
  ost << plot.RESOLUTION.first << " " << plot.RESOLUTION.second << std::endl;

  /*
   * Put the actual greydata into the stream.
   */
  for ( int j = 0 ; j < plot.RESOLUTION.second ; ++j )
    {
      for ( int i = 0 ; i < plot.RESOLUTION.first ; ++i )
        {
          /*
           * Get the greyvalue, put it and a following space into the stream.
           */
          ost << plot.histogram[j * plot.RESOLUTION.first + i] << " ";
        }
      ost << std::endl;
    }

  /*
   * Return the outstream.
   */
  return ost;
};



std::istream &
operator>> (std::stringstream & ist, Histogram & plot)
{
  /*
   * Make sure the file dimensions match the dimensions of plot. Throw 
   * an exception if the dimensions of plot don't match.
   */
  long new_width, new_height = 0;
  ist >> new_width >> new_height;

  if ( new_width != plot.RESOLUTION.first
      || new_width != plot.RESOLUTION.second )
    throw std::invalid_argument ("Histogram dimensions incompatible.");

  /*
   * Read the stream into actual greydata.
   */
  for ( unsigned long i = 0 ; i < plot.histogram.size () ; ++i )
    {
      /*
       * Read the next cell and add its value to the local cell.
       */
      long new_cell = 0;
      ist >> new_cell;
      plot.histogram[i] += new_cell;

      if ( plot.histogram[i] > plot.max_cell )
        plot.max_cell = plot.histogram[i];
    }

  /*
   * Return the instream.
   */
  return ist;
};



/*
 * This function resets each cell of the histogram to 0, and resets
 * max_cell to 0.
 */
void
Histogram::clear ()
{
  histogram = std::vector<long> (RESOLUTION.first * RESOLUTION.second, 0);
  max_cell = 0;
};



/*
 * This function gets the value of histogram at (x, y).
 */
long
Histogram::get_at (long const x, long const y) const
{
  return histogram[y*RESOLUTION.first + x];
};



/*
 * This function takes a list of complex points and plots any points in
 * the area defined by RANGE onto the histogram.
 */
void
Histogram::ins_pts (std::vector<std::complex<double>> const & points)
{
  /*
   * Mark each valid point on the histogram.
   */
  for ( auto const & point : points )
    {
      /*
       * Ignore point if it is not in RANGE.
       */
      if (
          std::real (point) < std::real (RANGE.first) ||
          std::imag (point) < std::imag (RANGE.first) ||
          std::real (point) > std::real (RANGE.second) ||
          std::imag (point) > std::imag (RANGE.second)
         )
        continue;

      /*
       * Compute the coordinates of the point on the histogram.
       */
      long x = (std::real (point) - std::real (RANGE.first)) / DELTA.first;
      long y = (std::imag (point) - std::imag (RANGE.first)) / DELTA.second;

      /*
       * Increment the histogram counter at (x, y).
       */
      ++histogram[y*RESOLUTION.first + x];
    }

  /*
   * Find the cell with the most points, record the value in max_cell.
   */
  for ( unsigned long i = 0 ; i < histogram.size () ; ++i )
    if ( histogram[i] > max_cell )
      max_cell = histogram[i];
};



/*
 * This function just maps a histogram score to a greyscale value,
 * nothing special here.
 */
std::string
Histogram::get_color (long const score) const
{
  std::ostringstream convert;

  if (max_cell != 0)
    convert << static_cast<long> ( 255 * (static_cast<double> (score) / max_cell) );

  return convert.str();
};
