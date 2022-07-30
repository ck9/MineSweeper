#include "minesweeper.h"

/**
 * -2: 未開封、爆弾なし(safe)
 * -1: 未開封、爆弾あり(bomb)
 * 0-8: 開封済、数字が爆弾の個数 
 */
int map[20][20];

int dif; //難易度(0:easy, 1:normal, 2:hard)
int isMapGenerated; //爆弾が生成済か否かを管理するフラグ
int n[3] = {9, 16, 20}; //難易度ごとの盤面サイズ(n×n)
int bomb_n[3] = {10,40,80}; //難易度ごとの爆弾の個数
struct timespec start,end; //クリアタイム計測用

//難易度の設定を行うsetDifficulty関数
int setDifficulty(){
  do{
    printf("新しいゲームを開始します。\n");
    printf("難易度を選択してください。(0で終了)\n");
    printf("1: easy (%dx%d, 地雷%d個)\n", n[0], n[0], bomb_n[0]);
    printf("2: normal (%dx%d, 地雷%d個)\n", n[1], n[1], bomb_n[1]);
    printf("3: hard (%dx%d, 地雷%d個)\n", n[2], n[2], bomb_n[2]);
    scanf("%d", &dif);
    if(dif == 0){
      printf("ゲームを終了します。\n");
      return 0;
    }
    dif--;
  } while(dif < 0 || 2 < dif);
  printf("\n");
  printf("====================\n");
  printf("マインスイーパー！\n");
  switch (dif){
  case 0:
    printf("難易度: easy\n");
    break;
  case 1:
    printf("難易度: normal\n");
    break;
  case 2:
    printf("難易度: hard\n");
    break;
  }
  printf("盤面サイズ: %d x %d\n", n[dif], n[dif]);
  printf("爆弾個数: %d個\n", bomb_n[dif]);
  printf("====================\n");
  printf("\n");
  resetMap(); //盤面を初期化する
  return 1;
}

//指定マスを開くopen関数
int open(x, y){
  if(isMapGenerated == 0){ //盤面を生成していないなら
    generateBomb(x, y); //爆弾を生成
    isMapGenerated = 1; //盤面を生成したことを管理する変数を1にする
  }
  if(x<0||n[dif]<=x||y<0||n[dif]<=y){
    printf("マップの範囲外です。\n");
    return -2;
  }
  if(map[x][y] == -2){ //未開封なら
    map[x][y] = countBombAround(x, y); //周囲の爆弾の個数を数える
    if(map[x][y] == 0){ //周囲の爆弾が0なら
      for(int i=x-1; i<=x+1; i++){
        for(int j=y-1; j<=y+1; j++){
          if(i>=0 && i<n[dif] && j>=0 && j<n[dif]){
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
      if(i>=0 && i<n[dif] && j>=0 && j<n[dif]){
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
  for(int i=0; i<n[dif]; i++){
    for(int j=0; j<n[dif]; j++){
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
    timespec_get(&end, TIME_UTC); //開始時間を取得
    return 1;
  }
  else{
    return 0;
  }
}

//盤面を初期化するresetMap関数
void resetMap(){
  for(int i=0; i<n[dif]; i++){
    for(int j=0; j<n[dif]; j++){
      map[i][j] = -2;
    }
  }
  isMapGenerated = 0; //爆弾を生成していないことを管理する変数を0にする
}

//マップ内に爆弾を生成するgenerateBomb関数
void generateBomb(x, y){
  srand(time(NULL));
  int i, j;
  for(int k=0; k<bomb_n[dif]; ){
    i = rand() % n[dif];
    j = rand() % n[dif];
    //1手目の位置(or周囲)に爆弾生成されることを防ぐ
    if(map[i][j] != -1 && (abs(i-x)>1 || abs(j-y)>1)){
      map[i][j] = -1;
      k++;
    }
  }
  timespec_get(&start, TIME_UTC); //クリアタイム計測開始
}

/** 
 * マップを画面に表示するprintMap関数
 * mode=0: 爆弾非表示, mode=1: 爆弾表示(答え出力)
 */
void printMap(int mode){
  if(mode==1)
    printf("=========答え=========\n");
  printf("\n");
  for (int i = -1; i <= n[dif]; i++){
    switch (i){
      case -1:
        printf("   ");
        break;
      case 0:
        printf("|");
        break;
      default:
        printf("%2c", int2char(i));
        break;
    }
  }
  printf("\n");
  for (int i = 0; i <= n[dif]+1; i++){
    if(i==1)
      printf("-+-");
    else
      printf("--");
  }
  printf("\n");
  for(int i=0; i<n[dif]; i++){
    if(i+1<=9)
      printf("%2d | ", i+1);
    else
      printf("%2c | ", int2char(i+1));
    for(int j=0; j<n[dif]; j++){
      switch (map[i][j]){
        case -2:
          printf("□ ");
          break;
        case -1:
          if(mode==0)
            printf("□ ");
          else
            printf("* ");
          break;
        case 0:
          printf("  ");
          break;
        default:
          printf("%d ", map[i][j]);
          break;
      }
    }
    printf("\n");
  }
  printf("\n");
}

//数字をアルファベット表記に変換するint2char関数
char int2char(int i){
  if(i<=9)
    return i+'0';
  else
    return i+'a'-10;
}

//アルファベット表記を数字に変換するchar2int関数
int char2int(char c){
  if('0'<=c && c<='9')
    return c-'0';
  else
    return c-'a'+10;
}

//クリア時間を取得するgetClearTime関数
void getClearTime(){
  long nsec;
  long long tsec;
  if (start.tv_nsec < end.tv_nsec) {
    nsec = end.tv_nsec - start.tv_nsec;
    tsec = end.tv_sec - start.tv_sec;
  }
  else {
    nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    tsec = end.tv_sec - start.tv_sec - 1;
  }
  printf("クリア時間：%lld.%ld秒\n\n", tsec, nsec/1000000);
}