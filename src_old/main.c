#include <stdio.h>

typedef struct {
    char name[20];  // 商品名
    int price;      // 価格
    int stock;      // 在庫数
} Product;

void showProducts(void);
void buyProduct(void);

Product products[3] = {
    {"コーラ", 120, 5},
    {"お茶", 100, 0},
    {"水", 80, 10}
};

int main(void) {
    for (;;) {
        showProducts();
        buyProduct();
    }

    return 0;
}

void showProducts(void) {
    printf("=== 商品一覧 ===\n");
    for (int i = 0; i < 3; i++) {
        printf("%d %s %d円\n", i, products[i].name, products[i].price);
    }
}

void buyProduct(void) {
    int productID;                  //商品番号
    int money;                      //投入金額
    int NUM_PRODUCTS = 3;           //商品数

    printf("購入する商品を選んでください:");
    scanf("%d", &productID);

    while (1) {
        for (int i = 0; productID < 0 || productID >= NUM_PRODUCTS; i++) {
            printf("商品番号が間違っています。もう一度入力してください:");
            scanf("%d", &productID);
        }

        if (products[productID].stock > 0) {
            printf("商品名: %s, 価格: %d円\n", products[productID].name, products[productID].price);
            printf("投入金額を入力してください: ");
            scanf("%d", &money);

            while (money < products[productID].price) {
                printf("金額が足りません。もう一度入力してください:");
                scanf("%d", &money);
            }

            printf("商品を排出しました。\n");

            int change = money - products[productID].price;
            printf("お釣り: %d円\n", change);               //お釣りの計算


            products[productID].stock--;    //在庫数減らす

            printf("ご購入ありがとうございます！\n");
            break;

        } else {
            printf("売り切れです。別の商品を選んでください。\n");
            printf("購入する商品の番号を選んでください:");
            scanf("%d", &productID);
        }
    }
}