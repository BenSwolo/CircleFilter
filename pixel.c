#include "pixel.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_my_pixel	*new_pixelarray(int width, int height)
{
  t_my_pixel	*new_array;

  new_array = malloc(sizeof(t_my_pixel) * (width * height));
  for (int i = 0; i < (width * height); i++)
    {
      new_array[i].red = 255;
      new_array[i].green = 255;
      new_array[i].blue = 255;
    }
  return (new_array);
}

void		pixelarray_cpy(t_my_pixel *src, t_my_pixel *dest,
			       int width, int height,
			       int x_begin, int y_begin,
			       int x_max, int y_max)
{
  int		pos;
  
  for (int y = 0; y < y_max && y + y_begin < height; y++)
    {
      for (int x = 0; x < x_max && x + x_begin < width; x++)
	{
	  pos = ((y_begin + y) * width) + x_begin + x;
	  dest[pos] = src[pos];
	}
    }
}

int		compare_pixelarray(t_my_pixel *array1, t_my_pixel *array2,
				   int width, int height,
				   int x_begin, int y_begin,
				   int x_max, int y_max)
{
  int		diff;
  int		color_diff;
  int		pos;
  
  diff = 0;
  for (int y = 0; y < y_max && y_begin + y < height; y++)
    {
      for (int x = 0; x < x_max && x_begin + x < width; x++)
	{
	  pos = ((y_begin + y) * width) + x_begin + x;

	  diff += (pow(array1[pos].red - array2[pos].red, 2) +
		   pow(array1[pos].green - array2[pos].green, 2) +
		   pow(array1[pos].blue - array2[pos].blue, 2));
	}
    }
  //printf("%d ", diff);
  return (diff);
}
