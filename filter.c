#include "filter.h"
#include "display.h"
#include <time.h>
#include <stdlib.h>

t_my_pixel	*my_filter(t_my_pixel *pixel_array, t_list *colors,
			   int width, int height)
{
  t_my_pixel	new_pixel;
  int		radius_max;
  t_my_pixel	*new_array;
  t_my_pixel	*tmp_array;
  time_t	then, now;
  int		palette_size;
  int		match;
  int		tmp_match;
  int		x, y, size, pos;
  
  new_array = NULL;
  palette_size = listlen(colors);
  //printf("%d %d\n", width, height);
  if (width > height)
    radius_max = height;
  else
    radius_max = width;
  srand(time(NULL));
  time(&then);
  time(&now);
  tmp_array = new_pixelarray(width, height);
  new_array = new_pixelarray(width, height);
  while (difftime(now, then) < 30)
    {
      //new_pixel = get_elem(colors, rand() % palette_size);
      new_pixel.red = rand() % 255;
      new_pixel.blue = rand() % 255;
      new_pixel.green = rand() % 255;
      x = rand() % width;
      y = rand() % height;
      size = (rand() % 8) + 3;
      pos = (y * width) + x;
      x -= size;
      if (x < 0)
	x = 0;
      y -= size;
      if (y < 0)
	y = 0;
      my_putcircle(x, y, size,
		   new_pixel, tmp_array, width, height);
      tmp_match = compare_pixelarray(tmp_array, pixel_array,
				     width, height,
				     x, y,
				     size * 2, size * 2);
      match = compare_pixelarray(new_array, pixel_array,
				 width, height,
				 x, y,
				 size * 2, size * 2);
      if (tmp_match <= match)
	{
	  my_putcircle(x, y, size,
		       new_pixel, new_array, width, height);
	}
      else
	pixelarray_cpy(new_array, tmp_array,
		       width, height,
		       x, y,
		       size * 2, size * 2);
      //printf("\n");
      time(&now);
    }
  return (new_array);
}
