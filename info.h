#ifndef _INFO_H__
# define _INFO_H__

typedef struct		s_my_info_header
{
  uint32_t		header_size;
  uint32_t		width;
  uint32_t		height;
  short			nb_planes;
  short			bytes_per_pixel;
  uint32_t		pixel_compression;
  uint32_t		array_size;
  uint32_t		resolution[2];
  uint32_t		nb_colors;
  uint32_t		important_color;
} __attribute__((packed)) t_my_info_header;

#endif
