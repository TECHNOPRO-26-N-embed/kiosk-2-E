/*
1.  ユーザーに購入する商品の番号（ID)を入力させる
2.  商品番号が正しいか確認
3． 正しい場合->4.
    正しくない場合->「商品番号が間違っています」と表示->1.
4.  在庫があるか確認
5.  ある場合->6．
    ない場合->「売り切れ」と表示->1.
6.  商品名、価格を表示
7.  投入金額を入力
8.  価格=<投入金額の場合->9.
    価格>投入金額の場合->「金額が足りません」と表示->7.
9.  商品排出
10. お釣りを返す
11. 在庫を1減らす
12. 購入完了*/

#include <stdio.h>
typedef struct {
    char name[20];  //商品名
    int price;      //価格
    int stock;      //在庫数
} Product;


void buyProduct();


Product products[3]={
    {"コーラ", 120, 5},
    {"お茶", 100, 3},
    {"水", 80, 10}

}; //商品数は3と仮定




int main() {
    buyProduct();
    return 0;
}




void buyProduct(){
    int productID;            //商品番号
    int money;                //投入金額
    int NUM_PRODUCTS = 3;    //商品数

    printf("購入する商品の番号を選んでください:");
    scanf("%d", &productID);

    while(1){
        for (int i = 0; productID < 0 || productID >= NUM_PRODUCTS; i++){
            printf("商品番号が間違っています。もう一度入力してください。:");
            scanf("%d", &productID);
        }
        
        //products[productID] は、商品番号 productID に対応する商品を表す構造体であると仮定してます。
        //products[productID].stock　その商品の在庫数
        //products[productID].name その商品の名前
        //products[productID].price その商品の価格

        if (products[productID].stock > 0){
            printf("商品名: %s, 価格: %d円\n", products[productID].name, products[productID].price);
            printf("投入金額を入力してください: ");
            scanf("%d", &money);
            while (money < products[productID].price){
                printf("金額が足りません。もう一度入力してください。:");
                scanf("%d", &money);
            }

            printf("商品を排出しました。\n");
            
            int change = money - products[productID].price;   //お釣りの計算
            printf("お釣り: %d円\n", change);

            products[productID].stock--;  //在庫を1減らす

            printf("ご購入ありがとうございます！\n");
            break;

        }
        else{
            printf("売り切れです。別の商品を選んでください。\n");
            printf("購入する商品の番号を選んでください：");
            scanf("%d", &productID);
        }
    }
}