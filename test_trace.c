#include	"mytrace.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/* ----------------------------------------------------------------------------
	関数の定義
---------------------------------------------------------------------------- */
extern	void sub1();
extern	void sub11();
extern	void sub111();
extern	void sub2();
extern	void sub21();
extern	void sub211();
extern	void sub3();
extern	void sub31();
extern	void sub311();
extern	void sub4();
extern	void sub41();
extern	void sub411();
extern	void sub5();
extern	void sub51();
extern	void sub511();

int		mytrace_test()
{

	TR_INIT();
//	gCounter = 0xfffffffffffffff8;

	sub1();	
		TR_FPRINT();	
	sub2();
		TR_FPRINT();
	sub3();
		TR_FPRINT();
	sub4();
		TR_FPRINT();
	sub5();
		TR_FPRINT();

	TR_TERM();
	return 0;
}


int		main(int argc, char *argv[])
{

	mytrace_test();
	return 0;
}
