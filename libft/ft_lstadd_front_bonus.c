/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 20:03:04 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/25 20:16:04 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*La función ft_lstadd_front agrega el elemento new al principio de la 
lista enlazada lst.
Si lst es un puntero nulo, se considera que la lista está vacía y 
new se convierte en la cabeza de la lista.*/