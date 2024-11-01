#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LIMIT 10000

int N, K;
int best_MAX = 0;
int best_set[15];
int current_set[15];
int dp[MAX_LIMIT];

void compute_max(int *stamps, int K, int *max_val){
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    for(int i=0;i<K;i++){
        int stamp = stamps[i];
        for(int j=stamp; j<MAX_LIMIT; j++){
            if(dp[j - stamp] +1 < dp[j]){
                dp[j] = dp[j - stamp] +1;
            }
        }
    }
    int m = 0;
    while(m+1 < MAX_LIMIT && dp[m+1] <= N){
        m++;
    }
    if(m > *max_val){
        *max_val = m;
        memcpy(best_set, stamps, sizeof(int)*K);
        best_MAX = m;
    }
    else if(m == *max_val){
        for(int i=0;i<K;i++) {
            if(stamps[i] < best_set[i]){
                memcpy(best_set, stamps, sizeof(int)*K);
                break;
            }
            else if(stamps[i] > best_set[i]){
                break;
            }
        }
    }
}

void backtrack(int pos, int start, int K){
    if(pos == K){
        compute_max(current_set, K, &best_MAX);
        return;
    }
    for(int i=start; i <= MAX_LIMIT && (MAX_LIMIT - start) >= (K - pos); i++){
        current_set[pos] = i;
        backtrack(pos+1, i+1, K);
    }
}

int main(){
    scanf("%d %d", &N, &K);
    current_set[0] = 1;
    backtrack(1, 2, K);
    for(int i=0;i<K;i++){
        printf("%d%c", best_set[i], (i==K-1)?'\n':' ');
    }
    printf("MAX=%d\n", best_MAX);
    return 0;
}