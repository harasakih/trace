#
# $(Id) : $
#	マクロ定義
#		$@	ターゲット（サフィックスあり）
#		$*	ターゲット（サフィックスなし）
#		$<	最初の、依存ファイル
#		$^	全ての、依存ファイル
#
# 新たに追加するサフィックス(.c .o .h .a)以外
MY_OS = linux
SUF_C   = .c
SUF_OBJ = .o
SUF_EXE =

.SUFFIXES: $(SUF_OBJ) $(SUF_EXE)

#	コマンドの定義
CC		= clang
RM		= rm
# ECHO	= "/bin/echo -n"
ECHO	= echo -n

#	コンパイルオプション
# C_FLGS	= -Wall		; gcc warn-all
# C_FLGS	= /Wall		; vc++ warn-all
C_FLGS_D	= -ggdb
C_FLGS_R	=
C_FLGS		= -Wall -fPIC $(C_FLGS_R)

#	環境変数
export TRACEFILE=trace
export TRACEMAX=20
export LD_LIBRARY_PATH=./

#	デフォルト生成規則
#
.c.o:
	$(ECHO) ### implicit rules .c -> .o ###
	$(CC) -c $(C_FLGS) $<

.o:
	$(ECHO) ### implicit rules .o -> .exe ###
	$(CC) $(LD_FLGS) -o $@ $< $(LIBS)

.c:
	$(ECHO) ### implicit rules .c -> .exe ###
	$(CC) $(C_FLGS) $(LD_FLGS) -o $@ $< $(LIBS)

#	このファイルのターゲット＆ソース
ALL_EXE	= test_trace
ALL_OBJ = test_trace.o mytrace.o \
  test_trace_sub1.o test_trace_sub2.o test_trace_sub3.o \
  test_trace_sub4.o test_trace_sub5.o 
ALL_LIB = libmytrace.so libtest_trace_sub1.so libtest_trace_sub2.so libtest_trace_sub3.so libtest_trace_sub4.so libtest_trace_sub5.so
ALL_TRACE = $(TRACEFILE)*

dummy: 
	$(ECHO) ###########################################################
	$(ECHO) ##                                                       ##
	$(ECHO) ##     makefile for gcc $(MY_OS) version                 ##
	$(ECHO) ##                                                       ##
	$(ECHO) ###########################################################

all: test_trace

# TARGET
test_trace: test_trace.o $(ALL_LIB)
	$(CC) $(C_FLGS) -o $@ $< -L. -lmytrace \
	  -ltest_trace_sub1 -ltest_trace_sub2 -ltest_trace_sub3 -ltest_trace_sub4 -ltest_trace_sub5
#NG	$(CC) $(C_FLGS_D) -o $@ $< -L. -ltest_trace_sub -lmytrace 
#NG	$(CC) $(C_FLGS_D) -ldl -rdynamic -o $@ $< 

# SHARED-LIB
libtest_trace_sub1.so: test_trace_sub1.o libmytrace.so
	$(CC) $(C_FLGS) -shared -o $@ $< -L. -lmytrace

libtest_trace_sub2.so: test_trace_sub2.o libmytrace.so
	$(CC) $(C_FLGS) -shared -o $@ $< -L. -lmytrace

libtest_trace_sub3.so: test_trace_sub3.o libmytrace.so
	$(CC) $(C_FLGS) -shared -o $@ $< -L. -lmytrace

libtest_trace_sub4.so: test_trace_sub4.o libmytrace.so
	$(CC) $(C_FLGS) -shared -o $@ $< -L. -lmytrace

libtest_trace_sub5.so: test_trace_sub5.o libmytrace.so
	$(CC) $(C_FLGS) -shared -o $@ $< -L. -lmytrace

# SHARED-LIB
libmytrace.so: mytrace.o
	$(CC) $(C_FLGS) -shared -o $@ $< -ldl -rdynamic 

clean: 
	-$(RM) $(ALL_EXE) $(ALL_OBJ) $(ALL_LIB) $(ALL_TRACE)

rebuild:  clean all

test: test_trace
	./test_trace
