#include <stdio.h>
#include <time.h>

void savePurchase(char productName[], int price) {
    FILE *fp;
    fp = fopen("purchase_history.csv", "a");

    if (fp == NULL) {
        printf("ファイルを開けません\n");
        return;
    }

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char time_str[20];
    strftime(time_str, 20 , "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(fp, "%s,%d,%s\n", productName, price, time_str);

     fclose(fp);
}