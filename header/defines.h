/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 20:47:12 by gyeon             #+#    #+#             */
/*   Updated: 2022/01/25 20:47:13 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# define TRUE	1
# define FALSE	0
# define FLG_SQ 0b00000001
# define FLG_DQ 0b00000010
# define FLG_DL 0b00000100
# define FLG_RD 0b00001000
# define NOT_ALP_NUM	'n'
# define WHITE			'W'
# define PIPE			'P'
# define RR				'Q'
# define RRR			'R'
# define LR				'S'
# define LRR			'T'
# define ALNUM			'A'
# define EXCL			'~'
# define FIN			'F'
# define DLQUESTION		'?'
# define J		0
# define CJI	1
# define EJI	2
# define HJI	18
# define EIJ	3
# define CJINP	4
# define CJINR	5
# define CJJINR	6
# define CJINL	7
# define CJJINL	8
# define EJINP	9
# define EJINR	10
# define EJJINR	11
# define EJINL	12
# define EJJINL	13
# define CJIAW	14
# define EJIAW	15
# define CAF	16
# define EAF	17
# define P_ERR	19
# define CJIEJI	20
# define EJIEJI	21
# define APPEND	521		// O_WRONLY | O_APPEND | O_CREAT
# define OWRITE	1537	// O_WRONLY | O_TRUNC | O_CREAT
#endif
