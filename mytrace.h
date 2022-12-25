/* set TAB-SPACE:4
 *
 * TIME functions
 * TIME_RES(int *ret, int *NUM, struct timespec *ts) 
 * TIME_GET(int *ret, int *NUM, struct timespec *ts)
 *   ret:0(success),-1(fail)
 *   NUM:0(CLOCK_REALTIME)
 * TIME_CLOCK(int *ret, long *getclock, long *clockpersec) 
*/

#ifndef		_INC_MYTRACE
#define		_INC_MYTRACE

/* ----------------------------------------------------------------------------
	ＩＮＣＬＵＤＥファイル
---------------------------------------------------------------------------- */
#include	<stdio.h>
#include	<string.h>
#include	<time.h>
#define		__USE_GNU
#include	<dlfcn.h>

/* ----------------------------------------------------------------------------
	ＤＥＦＩＮＥ＆ＭＡＣＲＯ
---------------------------------------------------------------------------- */
#define		MAX_TRACESTACK	1000
#define		MAX_BUF_CALLER	32
#define		MAX_FNAME		128

/* ----------------------------------------------------------------------------
	関数プロトタイプ宣言
---------------------------------------------------------------------------- */
extern	int	TR_PUSH();
extern	int	TR_FPRINT();
extern	int	TR_INIT();
extern	int	TR_TERM();
extern	int	TR_SETSTART();
extern	int	TR_DIFFTIME(int *ret, struct timespec *ts_start, struct timespec *ts_end, long *diff_sec, long *diff_nsec);

/* ----------------------------------------------------------------------------
	構造体の定義
---------------------------------------------------------------------------- */
struct Trace
{
	struct timespec ts;	/* { time_t tv_sec,  long tv_nsec; }	*/
						/* sec from 1970/01/01, nano sec		*/
	 char	caller[MAX_BUF_CALLER];
};

#ifdef	_MYTRACE_MAIN
/* ----------------------------------------------------------------------------
	外部変数(Static)の定義
---------------------------------------------------------------------------- */
static	char			_mytrace_id[] = "mtyime.h";
static	struct	Trace	gTraceStack[MAX_TRACESTACK];	/* TRACE情報のSTACK			*/
static	unsigned long	gCounter		= 0;			/* serial counter to TR_PUSH	*/
static	int				gTraceStackMax	= 10;			/* 有効数 < MAX_TRACESTACK		*/
static	int				gIring			= 0;			/* RING-COUNTER				*/
static	struct timespec	gStartTs;						/* 経過時間の起点				*/
static	FILE			*gTraceFP	= NULL;
static	char			gTraceFname[MAX_FNAME];
static	int				gOpenCnt		= 0;			/* TRACE-FILEの連番(OPENされた回数)	*/

#else /* ifdef MAIN */

/* ----------------------------------------------------------------------------
	外部変数の宣言
---------------------------------------------------------------------------- */
extern	char			_mytrace_id[];
extern	struct Trace	gTraceStack[];
extern	unsigned long	gCounter;
extern	int 			gTraceStackMax;
extern	int				gIring;
extern	struct timespec	gStartTs;
extern	FILE			*gTraceFP;
extern	char			gTraceFname[];
extern	int				gOpenCnt;

#endif		/* ifdef	_MYTRACE_MAIN */
#endif		/* ifndef	__INC_MYTRACE */
