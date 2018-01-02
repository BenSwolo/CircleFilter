#include "display.h"

void	my_putpixel(unsigned int x, unsigned int y,
		    t_my_pixel new_pixel, t_my_pixel *pixel_array,
		    int width, int height)
{
  if (x >= width || y >= height)
    return;
  pixel_array[(y * width) + x] = new_pixel;
}

void	my_putcircle(int x0, int y0, int radius,
		     t_my_pixel new_pixel, t_my_pixel *pixel_array,
		     int width, int height)
{
  int	x = radius;
  int	y = 0;
  int	err = -radius;;
  int	lastY;
  
  while (x >= y)
    {
      lastY = y;
      err += y;
      ++y;
      err += y;
      my_putline(x0 - x, y0 + lastY, x0 + x, y0 + lastY, new_pixel, pixel_array, width, height);
      if (y != 0)
	my_putline(x0 - x, y0 - lastY, x0 + x, y0 - lastY, new_pixel, pixel_array, width, height);
      if (err >= 0)
        {
	  if (x != lastY)
	    {
	      my_putline(x0 - lastY, y0 + x, x0 + lastY, y0 + x,
			 new_pixel, pixel_array, width, height);
	      if (y != 0)
		my_putline(x0 - lastY, y0 - x, x0 + lastY, y0 - x,
			   new_pixel, pixel_array, width, height);
	    }
	  err -= x;
	  --x;
	  err -= x;
        }
    }
}

void	my_putline(int x0, int y0, int x1, int y1,
		   t_my_pixel new_pixel, t_my_pixel *pixel_array,
		   int width, int height)
{
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){
    my_putpixel(x0, y0, new_pixel, pixel_array, width, height);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }   
}

void	my_putfullcircle(int x0, int y0, int radius,
			 t_my_pixel new_pixel, t_my_pixel *pixel_array,
			 int width, int height)
{
  //intf("pos:%d,%d radius:%d, color:%d,%d,%d\n", x0, y0, radius,
  //	 new_pixel.red, new_pixel.green, new_pixel.blue);
  for (int i = 0; i <= radius; i++)
    my_putcircle(x0, y0, i, new_pixel, pixel_array, width, height);
}
