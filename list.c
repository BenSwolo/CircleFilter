#include "list.h"
#include <stdio.h>

void		add_elem(t_list **list, t_my_pixel color)
{
  t_list	*tmp;
  
  if (*list == NULL)
    {
      if (!(*list = malloc(sizeof(t_list))))
	exit(84);
      (*list)->color = color;
      (*list)->next = NULL;
      (*list)->prev = NULL;
    }
  else
    {
      tmp = *list;
      while (tmp->next)
	  tmp = tmp->next;
      if (!(tmp->next = malloc(sizeof(t_list))))
	exit(84);
      tmp->next->color = color;
      tmp->next->next = NULL;
      tmp->next->prev = tmp;
    }
}

int		listlen(t_list *list)
{
  int		len;
  
  len = 0;
  while (list)
    {
      len++;
      list = list->next;
    }
  return (len);
}

t_list		*listcpy(t_list *list)
{
  t_list	*cpy;

  cpy = NULL;
  while (list)
    {
      add_elem(&cpy, list->color);
      list = list->next;
    }
  return (cpy);
}

void		aff_elem(t_list *list)
{
  while (list)
    {
      printf("%d %d %d ", list->color.red, list->color.green, list->color.blue);
      list = list->next;
    }
  printf("\n");
}

void		insert_list(t_list **head, t_list *list,
			    t_list *newprev, t_list *newnext)
{
  if ((!newprev && !newnext) || !list)
    return;
  if (list == *head)
      *head = list->next;
  if (list->next)
    list->next->prev = list->prev;
  if (list->prev)
    list->prev->next = list->next;
  list->prev = newprev;
  if (newprev)
    newprev->next = list;
  list->next = newnext;
  if (newnext)
    {
      newnext->prev = list;
      if (newnext == *head)
	*head = list;
    }
}

int		find_elem(t_list *list, t_my_pixel color)
{
  while (list)
    {
      if (color.red == list->color.red &&
	  color.blue == list->color.blue &&
	  color.green == list->color.green)
	return (1);
      list = list->next;
    }
  return (0);
}

t_my_pixel	get_elem(t_list *list, int index)
{
  int		i;
  
  i = 0;
  while (list && i < index)
    {
      list = list->next;
      i++;
    }
  return (list->color);
}
