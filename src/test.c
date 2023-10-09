/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:20:31 by erigolon          #+#    #+#             */
/*   Updated: 2023/10/09 11:44:29 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	testing(t_minishell *ms)
{
	printf("\nExportar una variable de entorno:\n");
	char *exportArgs[] = { "NOMBRE_VARIABLE" , NULL}; // Reemplaza "NOMBRE_VARIABLE" por el nombre de la variable a exportar
	ft_export(ms, exportArgs);

	printf("\nListado de variables de entorno:\n");
    char *listArgs[] = { NULL }; // Argumento nulo para listar todas las variables
    ft_export(ms, listArgs);

	printf("\nCambio variable de entorno:\n");
	char *exportChange[] = { "NOMBRE_VARIABLE=MASMEJOR" , NULL};
	ft_export(ms, exportChange);

	printf("\nListado de variables de entorno:\n");
	ft_export(ms, listArgs);

	ft_env(ms);
}
