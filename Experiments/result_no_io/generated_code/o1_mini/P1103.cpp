#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000000

typedef struct {
    int height;
    int width;
} Book;

int compare(const void *a, const void *b){
    Book *ba = (Book *)a;
    Book *bb = (Book *)b;
    return ba->height - bb->height;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    Book books[100];
    for(int i=0;i<n;i++) scanf("%d %d", &books[i].height, &books[i].width);
    qsort(books, n, sizeof(Book), compare);
    int dp[101][101][201];
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            for(int l=0;l<=200;l++) {
                dp[i][j][l] = INF;
            }
        }
    }
    dp[0][0][0] = 0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n -k;j++){
            for(int l=0;l<=200;l++){
                if(dp[i-1][j][l] == INF) continue;
                // Not take book i
                if(dp[i][j][l] > dp[i-1][j][l]){
                    dp[i][j][l] = dp[i-1][j][l];
                }
                // Take book i
                if(j +1 <= n -k){
                    int cost = (l == 0) ? 0 : abs(books[i-1].width - l);
                    if(dp[i][j+1][books[i-1].width] > dp[i-1][j][l] + cost){
                        dp[i][j+1][books[i-1].width] = dp[i-1][j][l] + cost;
                    }
                }
            }
        }
    }
    int result = INF;
    for(int l=0;l<=200;l++) {
        if(dp[n][n -k][l] < result){
            result = dp[n][n -k][l];
        }
    }
    printf("%d\n", result);
    return 0;
}