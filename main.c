#include "parse_bmp.h"
#include "filter.h"
#include "list.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
  t_my_bmp_header	*header;
  t_my_info_header	*info;
  t_my_pixel		*pixel_array;
  int			offset;
  unsigned int		tmp;
  int			width, height;
  int			fd;
  t_list		*colors;
  int			nb_bytes;
  
  if (ac == 1)
    return (0);
  printf("reading bmp file...\n");
  header = read_header(av[1]);
  if (!header)
    return (1);
  info = read_info_header(av[1]);
  if (!info)
    return (1);
  offset = header->pixel_array_offset;
  width = info->width;
  height = info->height;
  nb_bytes = info->bytes_per_pixel;
  pixel_array = read_pixel_array(offset, av[1], width, height, nb_bytes);
  colors = get_colors(pixel_array, width, height);
  printf("putting little circles on the picture...\n");
  pixel_array = my_filter(pixel_array, colors, width, height);
  if (pixel_array)
    {
      fd = open(av[1], O_RDWR);
      for (int i= 0; i < offset; i++)
	read(fd, &tmp, 1);
      printf("Overwriting file...\n");
      write_pixel_array(fd, pixel_array, width, height, nb_bytes);
      close(fd);
      printf("Done.\n");  
  }
  free(header);
  free(info);
  free(pixel_array);
  return (0);
}
