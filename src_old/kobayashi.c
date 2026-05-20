int main(void) {
    int a,b,c;
    printf("投入金額:");
    scanf("%d", &a);

    printf("商品の値段:");
    scanf("%d", &b);

    c = a - b;

    printf("お釣り: %d\n , c");

    return 0;
}