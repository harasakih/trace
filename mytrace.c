/*
 * TRACE functions
*/

#define		_MYTRACE_MAIN

#include	"mytrace.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/* ----------------------------------------------------------------------------
	関数の定義
---------------------------------------------------------------------------- */
/*
 * NAME		: TR_PUSH
 * DESCRIPT	: push trace-info to gTraceStack[]
 * RETURN	: 0:success,-1:fail
 */
int		TR_PUSH()
{
/* 現在時刻 */
	struct timespec		ts;
	clock_gettime(CLOCK_REALTIME, &ts);

/* call元 */
	Dl_info info;
	dladdr(__builtin_return_address(0), &info);
/* 自分の関数名：取得できず
	char	myname[MAX_BUF_CALLER];
	myname	=	__func__;
*/
	char	*caller		= (char *)info.dli_sname;
	int		l_caller	= strlen(caller);
/* RING_BUFにpush */
	memcpy(&gTraceStack[gIring].ts, &ts, sizeof(ts));
	strncpy(gTraceStack[gIring].caller, caller, MAX_BUF_CALLER);	/* copy & padding 0x00 */
//	memset(gTraceStack[gIring].caller, 0x00, MAX_BUF_CALLER);
//	memcpy(gTraceStack[gIring].caller, caller, l_caller);

#ifdef	DBG
	int		i;
	char	*func;
	time_t	tv_sec;
	long	tv_nsec;
	printf("---- PUSH gIring=%d,%s\n", gIring, gTraceStack[gIring].caller);
	for(i = 0; i < gTraceStackMax; i++) {
		func	=	gTraceStack[i].caller;
		tv_sec	=	gTraceStack[i].ts.tv_sec;
		tv_nsec	=	gTraceStack[i].ts.tv_nsec;
		if(tv_sec > 0) { /* gTraceStack[]が初期値の時は出力しない */
			printf("[%02d]%-8s:%ld-%s", i, func, tv_nsec, ctime(&tv_sec));
		}
	}
	printf("----\n");
#endif

/* RING_BUFの位置を更新 */
	gCounter++;
	gIring++;
	if(gIring >= gTraceStackMax) {
#ifdef	DBG
		printf("gIring:%d -> 0\n", gIring);
#endif
		gIring	=	0;
	}
	return 0;
}

/*
 * NAME		: TR_INIT
 * DESCRIPT	: initialize gTrackStack[MAX_TRACESTACK], fopen, gettracemax;
 * RETURN	: 0:success,-1:fail
 */
int		TR_INIT()
{
	int		i;
/* initialize gTraceStack[] */
	for(i = 0; i < MAX_TRACESTACK; i++) {
		memset(&gTraceStack[i], 0x00, sizeof(struct Trace));
	}
	gCounter = 0;
	gIring	= 0;
/* 環境変数の取得 */
/*
 *	TRACEFILE	-> gTraceFname, gTraceFP
 *	TRACEMAX	-> gTraceStackMax
*/
	char	*envp;
	envp = getenv("TRACEFILE");
	if (envp == NULL) {
		gTraceFP = stderr;
		strncpy(gTraceFname, "", MAX_FNAME);
	} else {
#ifdef DBG
		printf("TRACEFILE[%s,%d,%d]\n", envp,strlen(envp), MAX_FNAME);
#endif
		if(strlen(envp) >= (MAX_FNAME - 3)) {
			fprintf(stderr, "TRACEFILE too long[%s]. less than %d\n", envp, (MAX_FNAME - 3));
			exit(-1);
		}
		sprintf(gTraceFname, "%s%03d", envp, gOpenCnt);
		gOpenCnt++;
/* 		strncpy(gTraceFname, envp, MAX_FNAME);	*/
		if( (gTraceFP = fopen(gTraceFname, "w")) == NULL){
			fprintf(stderr, "Cannot open file[%s]\n", gTraceFname);
			exit(-1);
		}
	}

	envp = getenv("TRACEMAX");
	if (envp == NULL) {
		;
	} else {
		if( sscanf(envp, "%d", &gTraceStackMax) != 1) {
			fprintf(stderr, "Cannot getenv TRACEMAX[%s]\n", envp);
			exit(-1);
		}
	}
/* set gStartTs to now()	*/
	TR_SETSTART();
	return 0;
}

/*
 * NAME		: TR_TERM
 * DESCRIPT	: initialize gTrackStack[MAX_TRACESTACK]
 * RETURN	: 0:success,-1:fail
 */
int		TR_TERM()
{
	fclose(gTraceFP);
	return 0;
}

/*
 * NAME		: TR_SETTART
 * DESCRIPT	: set START time of interval
 * RETURN	: 0:success,-1:fail
 */
int		TR_SETSTART()
{
	clock_gettime(CLOCK_REALTIME, &gStartTs);
	return	0;
}

/*
 * NAME		: tr_difftime
 * DESCRIPT	: calc interval time
 * 
 * RETURN	: 0:success,-1:fail
 */
int		TR_DIFFTIME(int *ret, struct timespec *ts_start, struct timespec *ts_end, long *diff_sec, long *diff_nsec)
{
	*ret = 0;
	long	tmp_nsec;
	tmp_nsec	= ts_end->tv_nsec - ts_start->tv_nsec;
	if(tmp_nsec >= 0) {
		*diff_sec	= ts_end->tv_sec - ts_start->tv_sec;
		*diff_nsec	= tmp_nsec;
	} else {
		*diff_sec	= ts_end->tv_sec - ts_start->tv_sec - 1;
		*diff_nsec	= 1000000000 + tmp_nsec;
	}
	return 0;
}

/*
 * NAME		: TR_PRINT
 * DESCRIPT	: print trace-info from gTraceStack[]
 * RETURN	: 0:success,-1:fail
 */
#define		MAX_CTIME_BUF	128
int		TR_FPRINT()
{
	int		i, ii;
	int		iring;
	int		ll;
	int		ret;
	char	ctime_buf[MAX_CTIME_BUF];
	time_t	time_sec;
	long	diff_sec, diff_nsec;
	FILE	*fp;

	fp	= gTraceFP;
	fprintf(fp, "---- gCounter=%lu gTraceStackMax=%d gTraceFname=%s\n", gCounter, gTraceStackMax, gTraceFname);
	for(i = 0; i < gTraceStackMax; i++) {
	/* iring : RING_BUFの位置		*/
		ii		=	(gIring - i - 1);		/* gIringは次の位置に進んでいるので、一つ戻る */
		if(ii >= 0) { iring = ii; } 
		else 		{ iring = ii + gTraceStackMax; }
	/* timespecの秒を日付時刻に変換		*/
		time_sec	= gTraceStack[iring].ts.tv_sec;
		strncpy(ctime_buf, ctime(&time_sec), MAX_CTIME_BUF);
		ll	= strlen(ctime_buf);
		ctime_buf[ll - 1]  = 0x00;			/* 改行位置を00x00に変更	*/
	/* gStartTsからの経過時間を求める	*/
		TR_DIFFTIME(&ret, &gStartTs, &gTraceStack[iring].ts, &diff_sec, &diff_nsec);

		if(time_sec > 0) { /* gTraceStack[]が初期値の時は出力しない */
			fprintf(fp, "[%02d]%-8s:%s ELAPS[%ld.%09ldsec]\n",
				iring,
				gTraceStack[iring].caller,
				ctime_buf,
				diff_sec,
				diff_nsec
			);
		}
	}
	fprintf(fp, "----\n");
	return 0;
}
