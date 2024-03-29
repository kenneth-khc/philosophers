/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kecheong <kecheong@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:42:09 by kecheong          #+#    #+#             */
/*   Updated: 2024/02/23 14:42:42 by kecheong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# if 1
/* ANSI color codes */
#  define BLACK "\e[0;30m"
#  define MAGENTA "\e[0;31m"
#  define GREEN "\e[0;32m"
#  define YELLOW "\e[0;33m"
#  define BLUE "\e[0;34m"
#  define RED "\e[0;35m"
#  define BOLD_RED "\e[1;31m"
#  define CYAN "\e[0;36m"
#  define WHITE "\e[0;37m"
#  define COLOR_RESET "\e[0m"
#  define PADDING 10

# else /* toggle off colors for visualization */
#  define BLACK ""
#  define MAGENTA ""
#  define GREEN ""
#  define YELLOW ""
#  define BLUE ""
#  define RED ""
#  define BOLD_RED ""
#  define CYAN ""
#  define WHITE ""
#  define COLOR_RESET ""
#  define PADDING 0

# endif

#endif