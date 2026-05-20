#include <stdio.h>

#define ITEM_COUNT 3

char *positions[ITEM_COUNT] = {
    "A1", "A2", "A3"
};

char *names[ITEM_COUNT] = {
    "コーラ", "お茶", "水"
};

int prices[ITEM_COUNT] = {100, 100, 100};
int stocks[ITEM_COUNT] = {50, 50, 0};
int main(void) {
    int input;

    while (1) {
        printf("=== メニュー ===\n");
        printf("1: 商品一覧\n");
        printf("9: 終了\n");
        scanf("%d", &input);
        if (input == 1) {
            printf("=== 商品一覧 ===\n");
            for (int i = 0; i < ITEM_COUNT; i++) {
                printf("位置:%s 商品名:%s 価格:%d円 在庫:%d",
                       positions[i], names[i], prices[i], stocks[i]);
                if (stocks[i] == 0) {
                    printf(" （売り切れ）");
                }
                printf("\n");
            }
        } else if (input == 9) {
            printf("終了します\n");
            break;
        } else {
            printf("正しい番号を入力してください\n");
        }
    }
    return 0;
}