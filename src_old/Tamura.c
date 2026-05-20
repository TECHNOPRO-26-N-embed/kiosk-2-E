#include <stdio.h>

int main(void) {
    printf("=== メニュー ===\n");
    printf("1: 機能A\n");
    printf("2: 機能\n");
    printf("9: 終了\n");
    int menu;
    printf("メニューを選択してください：");
    scanf("%d", &menu);
    if (menu == 2) {
        printf("機能Bを選択しました。\n");
        while(1){
        int m;
        printf("金額を入力してください：");
    if(scanf("%d", &m) == 1){
        if(0 < m && m < 10000){
        printf("投入金額: %d\n", m);
        break;
        }else{
            printf("正しい値を入力してください。\n");
        }
    }else{
        printf("正しい値を入力してください。\n");
        while(getchar() != '\n');
    }
    }

    } else if (menu == 9) {
        printf("終了します。\n");
        return 0;
    } else {
        printf("無効なメニューです。\n");
        return 1;
    }

    return 0;
}