#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

int n;
int colors[505];
long long dp_cache[505][505][505];

long long dp(int i, int j, int k){
    if(i > j) return 0;
    if(dp_cache[i][j][k] != -1) return dp_cache[i][j][k];
    // Optimize k
    while(i < j && colors[j] == colors[j-1]){
        k++;
        j--;
    }
    // Initialize result
    long long res = dp(i, j-1, 0) + 1;
    for(int m = i; m < j; m++){
        if(colors[m] == colors[j]){
            long long temp = dp(i, m, k+1) + dp(m+1, j-1, 0);
            if(temp < res) res = temp;
        }
    }
    dp_cache[i][j][k] = res;
    return res;
}

int main(){
    memset(dp_cache, -1, sizeof(dp_cache));
    scanf("%d", &n);
    for(int i=0;i<n;i++) scanf("%d", &colors[i]);
    printf("%lld", dp(0, n-1, 0));
    return 0;
}