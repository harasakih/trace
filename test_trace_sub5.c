#include	"mytrace.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/* ----------------------------------------------------------------------------
	関数の定義
---------------------------------------------------------------------------- */
void	sub511()	{ printf("sub511\n")  ;TR_PUSH(); }
void	sub51()		{ printf("sub51\n")   ;TR_PUSH(); sub511(); }
void	sub5()		{ printf("sub5\n")    ;TR_PUSH(); sub51(); }

