#ifndef _FILTER_H__
# define _FILTER_H__

# include "parse_bmp.h"

t_my_pixel	*my_filter(t_my_pixel *pixel_array, t_list *colors,
			   int width, int height);

#endif /* _FILTER_H__ */
