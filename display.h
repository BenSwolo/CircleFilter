#ifndef _DISPLAY_H__
# define _DISPLAY_H__

# include "parse_bmp.h"

void	my_putpixel(unsigned int x, unsigned int y,
		    t_my_pixel new_pixel, t_my_pixel *pixel_array,
		    int width, int height);
void	my_putcircle(int x0, int y0, int radius,
		     t_my_pixel new_pixel, t_my_pixel *pixel_array,
		     int width, int height);
void	my_putfullcircle(int x0, int y0, int radius,
			 t_my_pixel new_pixel, t_my_pixel *pixel_array,
			 int width, int height);
void	my_putline(int x0, int y0, int x1, int y1,
		   t_my_pixel new_pixel, t_my_pixel *pixel_array,
		   int width, int height);

#endif /* _DISPLAY_H__ */
