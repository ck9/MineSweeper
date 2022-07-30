#include "minesweeper.h"

int main (){
  int x, y, flag;
  char char_x, char_y;
  while (setDifficulty()){ //ゲーム終了まで繰り返す
    while(1){
      printMap(0); //盤面を画面に表示
      printf("盤面内の数字は周囲の爆弾の個数です。\n");
      printf("開くマスを指定してください。(x y)\n");
      scanf("%*c%c", &char_x); //開くマスを指定
      scanf("%*c%c", &char_y);
      x = char2int(char_x); //char_xを数値に変換
      y = char2int(char_y); //char_yを数値に変換
      flag = open(y-1, x-1); //開くマスを開く
      if(flag == -1){ //爆弾があったら
        printf("\nゲームオーバー!\n\n");
        printMap(1); //盤面を画面に表示
        break;
      }
      else if(checkEnd() == 1){ //ゲーム終了したら
        printf("\nゲームクリア!\n");
        getClearTime();
        printMap(1); //盤面を画面に表示
        break;
      }
    }
  }
  return 0;
}
