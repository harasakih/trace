# trace
 C言語で関数呼出履歴（スタックトレース、バックトレース）を取得する。
- 関数の入口直後に、PUSH()を呼び出す、引数なし
- push()では、呼出元関数名、時刻を取得する
- 時刻取得しているので、ELAPS-TIMEから性能ネック箇所がわかる

## ヘッダファイル:mytrace.h

| 変数名 | 属性 | 設定値 | 説明 |
| :--- | :---| :--- | :--- |
| MAX_TRACESTACK | DEFINE | 1000 | RING-BUFの領域確保数 |
| MAX_BUF_CALLER | DEFINE | 32 | 呼出元関数名の最大長 |
| MAX_FNAME | DEFINE | 256 | ファイル名の最大長 |
| gCounter | unsigned long | 0 | push()の呼出回数、シリアル値で単調増加 |
| gTraceStackMax | int | 10 | 実際に使用するスタック数 *1 |
| gTraceFname | char * | null | スッタク情報の出力ファイル名、最大長は「MAX_FNAME」 *2 |

*1: 環境変数「TRACEMAX」で変更

*2: 環境変数「TRACEFILE」で変更。未設定時はstderrへ出力

## 関数一覧

| 関数名 | 概要 |
| :--- | :---|
| int TR_INIT() | 出力ファイルのOPEN,RING-BUFの初期化,ELAPS-TIMEの初期化 |
| int TR_PUSH() | トレース情報（関数名、時刻）の取得 |
| int TR_FPRINT() | トレース情報とELAPS-TIMEのファイル出力 |
| int TR_TERM() | 出力ファイルのCLOSE |
| int TR_SETSTART() | ELAPS-TIMEの初期化(起点時間の設定) |
| int TR_DIFFTIME() | ELAPS-TIMEの時間計算 |

## 使用例
```
void some_function {
	TR_INIT();
	sub1();	
	sub2();	
	sub3();	
	TR_FPRINT();
	TR_TERM();
}

void sub1()
{
	TR_PUSH();
// 関数の処理
}
```
## トレース情報の出力例
```
---- gCounter=15 gTraceStackMax=10 gTraceFname=
[04]sub511  :Mon Dec 19 01:12:53 2022 ELAPS[0.001373000sec]
[03]sub51   :Mon Dec 19 01:12:53 2022 ELAPS[0.001369000sec]
[02]sub5    :Mon Dec 19 01:12:53 2022 ELAPS[0.001365000sec]
[01]sub411  :Mon Dec 19 01:12:53 2022 ELAPS[0.001297000sec]
[00]sub41   :Mon Dec 19 01:12:53 2022 ELAPS[0.001294000sec]
[09]sub4    :Mon Dec 19 01:12:53 2022 ELAPS[0.001290000sec]
[08]sub311  :Mon Dec 19 01:12:53 2022 ELAPS[0.001222000sec]
[07]sub31   :Mon Dec 19 01:12:53 2022 ELAPS[0.001219000sec]
[06]sub3    :Mon Dec 19 01:12:53 2022 ELAPS[0.001215000sec]
[05]sub211  :Mon Dec 19 01:12:53 2022 ELAPS[0.001152000sec]
```



## make方法
 実行ファイルのリンク時に `-ldl -rdynamic`を指定する。

```
# TARGET
test_trace: test_trace.o $(ALL_LIB)
	$(CC) $(C_FLGS_D) -ldl -rdynamic -o $@ $< -L. -lmytrace \
	  -ltest_trace_sub1 -ltest_trace_sub2 -ltest_trace_sub3 \
	  -ltest_trace_sub4 -ltest_trace_sub5

# SHARED-LIB
libtest_trace_sub1.so: test_trace_sub1.o libmytrace.so
	$(CC) $(C_FLGS_D) -shared -o $@ $< -L. -lmytrace

# SHARED-LIB
libmytrace.so: mytrace.o
	$(CC) $(C_FLGS_D) -shared -o $@ $< 
```


