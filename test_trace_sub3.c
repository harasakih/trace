#include	"mytrace.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/* ----------------------------------------------------------------------------
	関数の定義
---------------------------------------------------------------------------- */
void	sub311()	{ printf("sub311\n")  ;TR_PUSH(); }
void	sub31()		{ printf("sub31\n")   ;TR_PUSH(); sub311(); }
void	sub3()		{ printf("sub3\n")    ;TR_PUSH(); sub31(); }
