#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int height;
    int width;
} Book;

int compare(const void* a, const void* b){
    Book *ba = (Book*)a;
    Book *bb = (Book*)b;
    return ba->height - bb->height;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    Book books[100];
    for(int i=0;i<n;i++) {
        scanf("%d %d", &books[i].height, &books[i].width);
    }
    qsort(books, n, sizeof(Book), compare);
    int m = n - k;
    long long dp[101][101];
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=m;j++) {
            dp[i][j] = 1e18;
        }
    }
    for(int i=0;i<n;i++) {
        dp[i][1] = 0;
    }
    for(int j=2;j<=m;j++) {
        for(int i=j-1;i<n;i++) {
            for(int k=0;k<i;k++) {
                if(dp[k][j-1] + abs(books[i].width - books[k].width) < dp[i][j]){
                    dp[i][j] = dp[k][j-1] + abs(books[i].width - books[k].width);
                }
            }
        }
    }
    long long res = 1e18;
    for(int i=m-1;i<n;i++) {
        if(dp[i][m] < res){
            res = dp[i][m];
        }
    }
    printf("%lld\n", res);
    return 0;
}