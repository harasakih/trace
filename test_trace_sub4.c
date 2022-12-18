#include	"mytrace.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/* ----------------------------------------------------------------------------
	関数の定義
---------------------------------------------------------------------------- */
void	sub411()	{ printf("sub411\n")  ;TR_PUSH(); }
void	sub41()		{ printf("sub41\n")   ;TR_PUSH(); sub411(); }
void	sub4()		{ printf("sub4\n")    ;TR_PUSH(); sub41(); }
