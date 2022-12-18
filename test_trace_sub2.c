#include	"mytrace.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/* ----------------------------------------------------------------------------
	関数の定義
---------------------------------------------------------------------------- */
void	sub211()	{ printf("sub211\n")  ;TR_PUSH(); }
void	sub21()		{ printf("sub21\n")   ;TR_PUSH(); sub211(); }
void	sub2()		{ printf("sub2\n")    ;TR_PUSH(); sub21(); }
