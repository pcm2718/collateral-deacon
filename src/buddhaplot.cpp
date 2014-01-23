#include "buddhaplot.hpp"



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
    for (auto const & y : plot.histogram)
      {
	for (auto const & x : y)
	  {
	    /*
	     * Get the greyvalue, put it and a following space into the stream.
	     */
	    ost << plot.get_color (x) << " ";
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
    return "5";
  };
