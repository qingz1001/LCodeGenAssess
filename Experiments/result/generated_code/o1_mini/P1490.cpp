#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_K 10

int n;
int minimal_k = 0;
long long count = 0;

// Function to calculate subset sums
void calculate_sums(int *set, int k, int *sums) {
    memset(sums, 0, (n+1) * sizeof(int));
    sums[0] = 1;
    for(int i = 0; i < k; i++) {
        for(int j = n; j >= set[i]; j--){
            if(sums[j - set[i]])
                sums[j] = 1;
        }
    }
}

// Recursive function to generate combinations
void backtrack(int start, int k, int *current, int depth, long long *res) {
    if(depth == k){
        int sums[MAX_N+1];
        calculate_sums(current, k, sums);
        for(int i =1;i<=n;i++) if(!sums[i]) return;
        (*res)++;
        return;
    }
    for(int i = start; i <= n - (k - depth) +1; i++){
        current[depth] = i;
        backtrack(i+1, k, current, depth+1, res);
    }
}

int main(){
    scanf("%d", &n);
    int current[MAX_K];
    for(int k=1; k<=MAX_K; k++){
        long long res =0;
        backtrack(1, k, current, 0, &res);
        if(res >0){
            minimal_k = k;
            count = res;
            break;
        }
    }
    printf("%d %lld", minimal_k, count);
    return 0;
}