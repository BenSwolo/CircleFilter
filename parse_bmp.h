#ifndef _PARSE_HH__
# define _PARSE_HH__

# include <stdint.h>
# include <stdio.h>
# include <inttypes.h>
# include "pixel.h"
# include "info.h"
# include "list.h"

typedef	struct		s_my_bmp_header
{
  char			id_field[2];
  uint32_t		size;
  short			unused[2];
  uint32_t		pixel_array_offset;
} __attribute__((packed)) t_my_bmp_header;



t_my_bmp_header		*read_header(const char *filename);
t_my_info_header	*read_info_header(const char *filename);
t_my_pixel		*read_pixel_array(int offset, const char *filename,
					  int width, int height, int nb_bytes);
void			write_pixel_array(int fd, t_my_pixel *pixel_array,
					  int width, int height, int nb_bytes);
void			write_header(FILE *fd, t_my_bmp_header header);
void			write_info_header(FILE *fd, t_my_info_header info);
t_list			*get_colors(t_my_pixel *pixel_array, int width, int height);

#endif /* _PARSE_HH__ */

