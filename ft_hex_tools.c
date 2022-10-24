/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:43:13 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/23 01:43:14 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <string.h>
#include <limits.h>

void reverse(char *x, int begin, int end)
{
   char c;

   if (begin >= end)
      return;

   c          = *(x+begin);
   *(x+begin) = *(x+end);
   *(x+end)   = c;

   reverse(x, ++begin, --end);
}

char *ft_itoh(int decimal)
{
	int temp;
	int quotient;
	char *hexadecimalNumber;
	int i;

	quotient = decimal;
	hexadecimalNumber = malloc(sizeof(char) * 10);
	i = 0;
	while(quotient!=0)
	{
		temp = quotient % 16;
		//To convert integer into character
		if( temp < 10)
		           temp =temp + 48; else
		         temp = temp + 55;
		hexadecimalNumber[i++]= temp;
		quotient = quotient / 16;
	}
	hexadecimalNumber[i] = 0;
	reverse(hexadecimalNumber, 0, i - 1);
	return (hexadecimalNumber);
}

int ft_htoi(char *hex)
{
	int	length;
	long long decimal;
	int i;
	int base;

	base = 1;
	decimal = 0;
	i = 0;
	length = strlen(hex);
    for(i = length--; i >= 0; i--)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - 48) * base;
            base *= 16;
        }
        else if(hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 55) * base;
            base *= 16;
        }
        else if(hex[i] >= 'a' && hex[i] <= 'f')
        {
            decimal += (hex[i] - 87) * base;
            base *= 16;
        }
    }
	return (decimal);
}
