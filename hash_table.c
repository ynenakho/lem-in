/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:13:18 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/27 15:33:00 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// typedef struct  s_art {
// 	char *name;
// 	int  price;
// }               t_art;





/*
** Utils
*/

// int		arts_len(t_art **arts)
// {
// 	int		len;

// 	len = 0;
// 	while (arts[len])
// 		len++;
// 	return (len);
// }

/*
**	List functions
*/

t_item			*ft_lstlast(t_item *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

void			ft_lstaddback(t_item **alst, t_item *new)
{
	if (*alst == NULL)
		*alst = new;
	else
		ft_lstlast(*alst)->next = new;
}

/*
**	Mandatory functions
*/

size_t			hash(char *input)
{
	size_t		hash;
	char		c;

	hash = 5381;
	while ((c = *input++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

t_dict	*dictInit(int capacity)
{
	t_dict		*res;
	size_t		size;

	res = malloc(sizeof(t_dict));
	size = sizeof(t_item *) * capacity;
	res->items = malloc(size);
	bzero(res->items, size);
	res->capacity = capacity;
	return (res);
}

int				dictInsert(struct s_dict *dict,
						char *key, t_room *room)
{
	int		i;
	t_item	*item;

	i = hash(key) % dict->capacity;
	item = malloc(sizeof(t_item));
	if (!item)
		return (0);
	item->key = key;
	item->room = room;
	item->next = NULL;
	ft_lstaddback(&dict->items[i], item);
	return (i);
}

t_room *dictSearch(struct s_dict *dict, char *key)
{
	int		i;
	t_item	*list;

	i = hash(key) % dict->capacity;
	list = dict->items[i];
	while (list) {
		if (strcmp(list->room->room_name, key) == 0)
			return (list->room);
		list = list->next;
	}
	return (NULL);
}

void		find(t_dict *d, char *key) {
	t_room	*room;

	room = dictSearch(d, key);
	if (room)
		printf("Room: name \'%s\' coords (%d,%d) start - %d end - %d Index = %d\n", room->room_name, room->x, room->y, room->start, room->end, room->index);
	else
		printf("Room not found. Key: %s\n", key);
}