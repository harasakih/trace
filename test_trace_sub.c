#include	"mytrace.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/* ----------------------------------------------------------------------------
	関数の定義
---------------------------------------------------------------------------- */

void	sub111()	{ printf("sub111\n")  ;TR_PUSH(); }
void	sub11()		{ printf("sub11\n")   ;TR_PUSH(); sub111(); }
void	sub1()		{ printf("sub1\n")    ;TR_PUSH(); sub11(); }

void	sub211()	{ printf("sub211\n")  ;TR_PUSH(); }
void	sub21()		{ printf("sub21\n")   ;TR_PUSH(); sub211(); }
void	sub2()		{ printf("sub2\n")    ;TR_PUSH(); sub21(); }

void	sub311()	{ printf("sub311\n")  ;TR_PUSH(); }
void	sub31()		{ printf("sub31\n")   ;TR_PUSH(); sub311(); }
void	sub3()		{ printf("sub3\n")    ;TR_PUSH(); sub31(); }

void	sub411()	{ printf("sub411\n")  ;TR_PUSH(); }
void	sub41()		{ printf("sub41\n")   ;TR_PUSH(); sub411(); }
void	sub4()		{ printf("sub4\n")    ;TR_PUSH(); sub41(); }

void	sub511()	{ printf("sub511\n")  ;TR_PUSH(); }
void	sub51()		{ printf("sub51\n")   ;TR_PUSH(); sub511(); }
void	sub5()		{ printf("sub5\n")    ;TR_PUSH(); sub51(); }

