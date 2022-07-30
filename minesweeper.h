#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int setDifficulty(); //難易度の設定を行うsetDifficulty関数のプロトタイプ宣言
void resetMap(); //盤面を初期化するresetMap関数のプロトタイプ宣言 
void generateBomb(int x, int y); //爆弾を生成するgenerateBomb関数のプロトタイプ宣言
int open(int x, int y); //指定マスを開くopen関数のプロトタイプ宣言
int countBombAround(int x, int y); //周囲の爆弾の個数を数えるcountBombAround関数のプロトタイプ宣言
int countSafe(); //安全な場所の個数を数えるcountSafe関数のプロトタイプ宣言
int checkEnd(); //ゲーム終了かどうかを判定するcheckEnd関数のプロトタイプ宣言
void printMap(int mode); //盤面を画面に表示するprintMap関数のプロトタイプ宣言
char int2char(int i); //数字をアルファベット表記に変換するint2char関数のプロトタイプ宣言
int char2int(char c); //アルファベット表記を数字に変換するchar2int関数のプロトタイプ宣言
void getClearTime();//クリア時間を取得するgetClearTime関数のプロトタイプ宣言