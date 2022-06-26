#include "minesweeper.h"

int main (){

  printf("====================\n");
  printf("マインスイーパー！\n");
  printf("盤面サイズ: %d x %d\n", N, N);
  printf("爆弾個数: %d個\n", BOMB_N);
  printf("====================\n");
  
  resetMap(); //盤面を初期化する
  int x, y, flag;
  while (1){ //ゲーム終了まで繰り返す
    printMap(0); //盤面を画面に表示
    printf("盤面内の数字は周囲の爆弾の個数です。\n");
    printf("開くマスを指定してください。(x y)\n");
    scanf("%d %d", &x, &y); //開くマスを指定
    flag = open(y-1, x-1); //開くマスを開く
    if(flag == -1){ //爆弾があったら
      printf("\nゲームオーバー!\n\n");
      printMap(1); //盤面を画面に表示
      break;
    }
    else if(checkEnd() == 1){ //ゲーム終了したら
      printf("\nゲームクリア!\n\n");
      printMap(1); //盤面を画面に表示
      break;
    }
  }

  return 0;
}

