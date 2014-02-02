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


/*
std::istream &
operator>> (std::istream & ist, Histogram & plot)
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
   * Write the maximum cell value.
   */
  //ost << plot.max_cell << std::endl;

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
   * Make sure the file dimensions match the dimensions of plot.
   */
  long new_width, new_height = 0;
  ist >> new_width >> new_height;

  // Add check here.

  /*
   * Read past max_cell.
   * This is a hack.
   */
  //long new_max = 0;
  //ist >> new_max;

  /*
   * Read the stream into actual greydata.
   */
  for ( int j = 0 ; j < plot.RESOLUTION.second ; ++j )
    {
      for ( int i = 0 ; i < plot.RESOLUTION.first ; ++i )
        {
          /*
           * Get the greyvalue, put it and a following space into the stream.
           */
          long new_cell = 0;
          ist >> new_cell;

          plot.histogram[j * plot.RESOLUTION.first + i] += new_cell;
        }
    }

  /*
   * Return the instream.
   */
  return ist;
};



void
Histogram::clear ()
{
  histogram = std::vector<long> (RESOLUTION.first * RESOLUTION.second, 0);
  max_cell = 0;
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
