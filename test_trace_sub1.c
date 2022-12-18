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
