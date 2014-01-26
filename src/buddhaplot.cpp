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
     * Set the maximum grey value file, currently fixed at 10.
     */
    ost << "10" << std::endl;

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



/*
 * Not yet implemented.
 */
std::string
Buddhaplot::get_color (long const & score) const
  {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 9);
    return std::to_string(dist(rd));
    // return "10";
  };
