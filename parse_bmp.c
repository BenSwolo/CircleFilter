#include "parse_bmp.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

t_my_bmp_header		*read_header(const char *filename)
{
  t_my_bmp_header	*header;
  int			fd;

  header = malloc(sizeof(t_my_bmp_header));
  fd = open(filename, 0);
  if (fd == -1)
    return (NULL);
  if (read(fd, header, sizeof(*header)) != sizeof(*header))
    return (NULL);
  if (header->id_field[0] != 'B' || header->id_field[1] != 'M')
    return (NULL);
  close(fd);
  return (header);
}

t_my_info_header	*read_info_header(const char *filename)
{
  t_my_info_header	*header;
  int			fd;
  void			*tmp;
  
  header = malloc(sizeof(t_my_info_header));
  fd = open(filename, 0);
  if (fd == -1)
    return (NULL);
  read(fd, tmp, 14);
  if (read(fd, header, sizeof(*header)) < sizeof(*header))
    return (NULL);
  close(fd);
  return (header);
}

t_my_pixel	*read_pixel_array(int offset, const char *filename,
				  int width, int height, int nb_bytes)
{
  t_my_pixel	*pixel_array;
  void		*tmp;
  int		fd;
  char		garbage;
  
  fd = open(filename, 0);
  if (fd == -1)
    return (NULL);
  read(fd, tmp, offset);
  pixel_array = malloc(sizeof(t_my_pixel) * (width * height));
  for (int y = height - 1; y >= 0; y--)
    {
      int bytes = 0;
      for (int x = 0; x < width; x++)
  	{
  	  read(fd, &pixel_array[(width * y) + x], 3);
	  if (nb_bytes == 32)
	    read(fd, &garbage, 1);
  	  bytes += 3;//(nb_bytes / 8);
  	}
      while (bytes % 4 != 0)
  	{
  	  read(fd, tmp, 1);
  	  bytes += 1;
  	}
    }
  close(fd);
  return (pixel_array);
}

void		write_pixel_array(int fd, t_my_pixel *pixel_array,
				  int width, int height, int nb_bytes)
{
  char		tmp = 0;
  int		bytes;
  char		garbage = 0;
  
  printf("writing...\n");
  for (int y = height - 1; y >= 0; y--)
    {
      bytes = 0;
      for (int x = 0; x < width; x++)
  	{
	  write(fd, &pixel_array[(width * y) + x].blue, 1);
	  write(fd, &pixel_array[(width * y) + x].green, 1);
	  write(fd, &pixel_array[(width * y) + x].red, 1);
	  if (nb_bytes == 32)
	    write(fd, &garbage, 1);
  	  bytes += 3;//(nb_bytes / 8);
  	}
      while (bytes % 4 != 0)
  	{
  	  write(fd, &tmp, 1);
  	  bytes += 1;
  	}
    }
}

t_list		*get_colors(t_my_pixel *pixel_array, int width, int height)
{
  t_list	*colors;

  colors = NULL;
  for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
	{
	  if (!find_elem(colors, pixel_array[(y * width) + x]))
	    add_elem(&colors, pixel_array[(y * width) + x]);
	}
    }
  return (colors);
}
			    

void		write_header(FILE *fd, t_my_bmp_header header)
{
  fwrite(&header.id_field, 2, 1, fd);
  fwrite(&header.size, sizeof(uint32_t), 1, fd);
  fwrite(&header.unused[0], 2, 1, fd);
  fwrite(&header.unused[1], 2, 1, fd);
  fwrite(&header.pixel_array_offset, sizeof(uint32_t), 1, fd);
}

void		write_info_header(FILE *fd, t_my_info_header info)
{
  unsigned int		tmp = 0;

  tmp = info.header_size;
  fwrite(&tmp, sizeof(tmp), 1, fd);
  tmp = info.width;
  fwrite(&tmp, sizeof(tmp), 1, fd);
  tmp = info.height;
  fwrite(&tmp, sizeof(tmp), 1, fd);

  /* fwrite(fd, &info.nb_planes, sizeof(short)); */
  /* fwrite(fd, &info.bytes_per_pixel, sizeof(short)); */
  /* fwrite(fd, &info.pixel_compression, sizeof(uint32_t)); */
  /* fwrite(fd, &info.array_size, sizeof(uint32_t)); */
  /* tmp = 0; */
  /* fwrite(fd, &tmp, sizeof(uint32_t)); */
  /* fwrite(fd, &tmp, sizeof(uint32_t)); */
  /* fwrite(fd, &info.nb_colors, sizeof(uint32_t)); */
  /* fwrite(fd, &info.important_color, sizeof(uint32_t)); */
}
