#ifndef _PIXEL_HH__
# define _PIXEL_HH__

typedef struct	s_my_pixel{

  unsigned char		blue;
  unsigned char		green;
  unsigned char		red;
} __attribute__((packed)) t_my_pixel;

t_my_pixel	*new_pixelarray(int width, int height);
int		compare_pixelarray(t_my_pixel *array1, t_my_pixel *array2,
				   int width, int height,
				   int x_begin, int y_begin,
				   int x_max, int y_max);
void		pixelarray_cpy(t_my_pixel *src, t_my_pixel *dest,
			       int width, int height,
			       int x_begin, int y_begin,
			       int x_max, int y_max);

#endif
