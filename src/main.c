#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 商品データ構造体
typedef struct {
    int id;
    char name[50];
    int price;
    int stock;
} Product;

// 商品データのサンプル
Product products[] = {
    {1, "コーラ", 120, 5},
    {2, "お茶", 100, 1},
    {3, "水", 80, 10}
};
int productCount = sizeof(products) / sizeof(products[0]);

// 商品リストを表示
void showProductList() {
    printf("\n商品リスト:\n");
    printf("ID\t商品名\t価格\t在庫\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d\t%s\t%d円\t%s\n", products[i].id, products[i].name, products[i].price,
               products[i].stock > 0 ? "在庫あり" : "売り切れ");
    }
}

// 投入金額を受け取る
#define MONEY_LIMIT 10000
int inputMoney() {
    char buf[32];
    int money;
    char *endptr;
    while (1) {
        printf("\n投入金額を入力してください（1～%d円）: ", MONEY_LIMIT);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("入力エラーです。再入力してください。\n");
            continue;
        }
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == 0) {
            printf("未入力です。再入力してください。\n");
            continue;
        }
        money = (int)strtol(buf, &endptr, 10);
        if (*endptr != '\0') {
            printf("数字のみを入力してください。\n");
            continue;
        }
        if (money <= 0) {
            printf("1円以上を入力してください。\n");
            continue;
        }
        if (money > MONEY_LIMIT) {
            printf("%d円以下で入力してください。\n", MONEY_LIMIT);
            continue;
        }
        return money;
    }
}

// お釣りを計算
int calcChange(int money, int price) {
    return money - price;
}

// 購入履歴を保存
void savePurchase(const char* productName, int price) {
    FILE *file = fopen("purchase_history.csv", "a");
    if (file == NULL) {
        printf("購入履歴の保存に失敗しました。\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(file, "%s,%d,%04d-%02d-%02d %02d:%02d:%02d\n",
            productName, price, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    fclose(file);
}

// 商品購入処理
void buyProduct() {
    showProductList();

    int productId;
    char idBuf[16];
    printf("\n購入したい商品のIDを入力してください: ");
    if (fgets(idBuf, sizeof(idBuf), stdin) == NULL) {
        printf("入力エラーです。\n");
        return;
    }
    if (sscanf(idBuf, "%d", &productId) != 1) {
        printf("無効な商品IDです。\n");
        return;
    }

    Product *selectedProduct = NULL;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == productId) {
            selectedProduct = &products[i];
            break;
        }
    }

    if (selectedProduct == NULL) {
        printf("無効な商品IDです。\n");
        return;
    }

    if (selectedProduct->stock <= 0) {
        printf("%sは売り切れです。\n", selectedProduct->name);
        return;
    }

    int money = 0;
    while (1) {
        money += inputMoney();
        if (money < selectedProduct->price) {
            printf("金額が不足しています。現在の投入金額: %d円\n", money);
            printf("%d円を返却します。\n", money);
            money = 0; // 返却後、投入金額をリセット
        } else {
            break;
        }
    }

    int change = calcChange(money, selectedProduct->price);
    printf("%sを購入しました。お釣り: %d円\n", selectedProduct->name, change);

    selectedProduct->stock--;
    savePurchase(selectedProduct->name, selectedProduct->price);
}

int main() {
    while (1) {
        printf("\n1. 商品リストを表示\n2. 商品を購入\n3. 終了\n選択: ");
        int choice;
        char buf[16];
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("入力エラーです。\n");
            continue;
        }
        if (sscanf(buf, "%d", &choice) != 1) {
            printf("数字で選択してください。\n");
            continue;
        }

        switch (choice) {
            case 1:
                showProductList();
                break;
            case 2:
                buyProduct();
                break;
            case 3:
                printf("終了します。\n");
                return 0;
            default:
                printf("無効な選択です。\n");
        }
    }
}