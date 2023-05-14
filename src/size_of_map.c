// Jason Brillante "Damdoshi"
// Pentacle Technologie 2009-2024
// Hanged Bunny Studio 2014-2022
// EFRITS SAS 2022-2024
//
// Pylos

#include		"program.h"

size_t			size_of_map(size_t			siz)
{
  return (siz * siz + (siz > 0 ? size_of_map(siz - 1) : 0));
}
