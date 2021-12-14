/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:10:25 by gyeon             #+#    #+#             */
/*   Updated: 2021/08/20 15:11:21 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    if (!*needle)
        return ((char *)haystack);
    while (haystack[i] != '\0' && i < len)
    {
        if (haystack[i] == needle[0])
        {
            while (needle[j] != '\0' && haystack[i + j] == needle[j] && i + j < len)
            {
                if (needle[j + 1] == '\0')
                    return((char *)&haystack[i]);
                j++;
            }
        }
        i++;
    }
    return (NULL);
}
