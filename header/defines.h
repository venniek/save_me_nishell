//
// Created by 연규준 on 2022/01/13.
//

#ifndef SAVE_ME_NISHELL_DEFINES_H
#define SAVE_ME_NISHELL_DEFINES_H

#define TRUE 1
#define FALSE 0

#define FLG_SQ 0b00000001	// 1
#define FLG_DQ 0b00000010	// 2
#define FLG_DL 0b00000100	// 4
#define FLG_RD 0b00001000	// 8
#define	NOT_ALP_NUM	'n'
#define WHITE 'W'
#define PIPE	'P'
#define RR		'Q'
#define RRR		'R'
#define LR		'S'
#define LRR		'T'
#define ALNUM 'A'
#define EXCL '~'
#define FIN 'F'

#define J 		0
#define CJI		1
#define EJI		2
#define HJI		18
#define EIJ		3
#define CJINP	4	//pipe
#define CJINR	5
#define CJJINR	6
#define CJINL	7
#define CJJINL	8
#define EJINP	9	//pipe
#define EJINR	10
#define EJJINR	11
#define EJINL	12
#define EJJINL	13

#define CJIAW	14
#define EJIAW	15
#define CAF		16
#define EAF		17
#define P_ERR	19

#define APPEND	O_WRONLY | O_APPEND | O_CREAT
#define OWRITE	O_WRONLY | O_TRUNC | O_CREAT

#endif //SAVE_ME_NISHELL_DEFINES_H
