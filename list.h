#ifndef _LIST_H__
# define _LIST_H__

# include "pixel.h"
# include <stdlib.h>

typedef struct	s_list
{
  t_my_pixel	color;
  struct s_list	*next;
  struct s_list	*prev;
}		t_list;

void		add_elem(t_list **list, t_my_pixel color);
void		aff_elem(t_list *list);
t_list		*listcpy(t_list *list);
int		listlen(t_list *list);
void		insert_list(t_list **head, t_list *list,
			    t_list *newprev, t_list *newnext);
int		find_elem(t_list *list, t_my_pixel color);
t_my_pixel	get_elem(t_list *list, int index);

#endif /* _LIST_H__ */
