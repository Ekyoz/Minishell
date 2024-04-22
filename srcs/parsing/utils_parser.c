/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atresall <atresall@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:52:07 by atresall          #+#    #+#             */
/*   Updated: 2024/04/19 15:52:07 by atresall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool check_char_before(char* chaine, char caractere, size_t position, int nbCaracteres) {
	// Vérifier que la position est valide et que le nombre de caractères à vérifier est positif
	if (position >= 0 && position < strlen(chaine) && nbCaracteres > 0) {
		// Calcul de la position de départ pour la vérification
		int debutVerification = position - nbCaracteres;
		if (debutVerification < 0) {
			debutVerification = 0; // Assurer que la vérification commence au début de la chaîne si nécessaire
		}

		// Parcourir la chaîne depuis la position de début jusqu'à la position donnée
		for (size_t i = debutVerification; i < position; i++) {
			// Vérifier si le caractère à la position courante est égal au caractère recherché
			if (chaine[i] == caractere) {
				return true; // Si trouvé, retourner vrai
			}
		}
	}
	return false; // Si non trouvé ou position invalide, retourner faux
}

bool check_char_after(char *string, char c, size_t pos, int len)
{
	if (pos < ft_strlen(string)-1)
		if(string[pos + len] != c)
			return false;
	return true;
}