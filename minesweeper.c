#include "minesweeper.h"

/**
 * -2: 未開封、爆弾なし(safe)
 * -1: 未開封、爆弾あり(bomb)
 * 0-8: 開封済、数字が爆弾の個数 
 */
int map[N][N];

//指定マスを開くopen関数
int open(x, y){
  static int isMapGenerated = 0; //盤面を生成したかどうかを管理する変数
  if(isMapGenerated == 0){ //盤面を生成していないなら
    generateBomb(x, y); //爆弾を生成
    isMapGenerated = 1; //盤面を生成したことを管理する変数を1にする
  }
  if(x<0||N<=x||y<0||N<=y){
    printf("マップの範囲外です。\n");
    return -2;
  }
  if(map[x][y] == -2){ //未開封なら
    map[x][y] = countBombAround(x, y); //周囲の爆弾の個数を数える
    if(map[x][y] == 0){ //周囲の爆弾が0なら
      for(int i=x-1; i<=x+1; i++){
        for(int j=y-1; j<=y+1; j++){
          if(i>=0 && i<N && j>=0 && j<N){
            open(i, j); //再帰処理で周囲のマスを開く
          }
        }
      }
    }
    return 0;
  }
  else if(map[x][y] == -1){ //爆弾なら
    return -1;
  }
  else{ //数字なら続行
    return 0;
  }
}

//周囲の爆弾の個数を数えるcountBombAround関数
int countBombAround(x, y){
  int count = 0;
  for(int i=x-1; i<=x+1; i++){
    for(int j=y-1; j<=y+1; j++){
      if(i>=0 && i<N && j>=0 && j<N){
        if(map[i][j] == -1){
          count++;
        }
      }
    }
  }
  return count;
}

//安全な場所の個数を数えるcountSafe関数
int countSafe(){
  int count = 0;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(map[i][j] == -2){
        count++;
      }
    }
  }
  return count;
}

//ゲーム終了かどうかを判定するcheckEnd関数
int checkEnd(){
  if (countSafe()==0){
    return 1;
  }
  else{
    return 0;
  }
}

//盤面を初期化するresetMap関数
void resetMap(){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      map[i][j] = -2;
    }
  }
}

//マップ内に爆弾を生成するgenerateBomb関数
void generateBomb(x, y){
  srand(time(NULL));
  int i, j;
  for(int k=0; k<BOMB_N; ){
    i = rand() % N;
    j = rand() % N;
    //1手目の位置(or周囲)に爆弾生成されることを防ぐ
    if(map[i][j] != -1 && (abs(i-x)>1 || abs(j-y)>1)){
      map[i][j] = -1;
      k++;
    }
  }
}

/** 
 * マップを画面に表示するprintMap関数
 * mode=0: 爆弾非表示, mode=1: 爆弾表示(答え出力)
 */
void printMap(int mode){
  if(mode==1)
    printf("=========答え=========\n");
  printf("\n");
  for (int i = -1; i <= N; i++){
    if(i==-1){
      printf("  ");
    }else if(i==0){
      printf("|");
    }else{
    printf("%2d",i);
    }
  }
  printf("\n");
  for (int i = 0; i <= N+1; i++){
    if(i==1)
      printf("+-");
    else
      printf("--");
  }
  printf("\n");
  for(int i=0; i<N; i++){
    printf("%2d| ",i+1);
    for(int j=0; j<N; j++){
      if(map[i][j]==-2){
        printf("□ ");
      }else if(map[i][j]==-1){
        if (mode==0)
          printf("□ ");
        else printf("* ");
      }else if(map[i][j]==0){
        printf("  ");
      }else{
        printf("%d ", map[i][j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}