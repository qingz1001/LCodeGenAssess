#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

int N;
long long S[MAX_N], A[MAX_N];
long long prefixSum[MAX_N];

int cmp(const void *a, const void *b) {
    int idx1 = *(int*)a;
    int idx2 = *(int*)b;
    if (S[idx1] != S[idx2]) {
        return S[idx1] - S[idx2];
    }
    return A[idx2] - A[idx1];
}

int main() {
    scanf("%d", &N);
    
    int indices[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%lld", &S[i]);
        indices[i] = i;
    }
    
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }
    
    qsort(indices, N, sizeof(int), cmp);
    
    prefixSum[0] = A[indices[0]];
    for (int i = 1; i < N; i++) {
        prefixSum[i] = prefixSum[i-1] + A[indices[i]];
    }
    
    long long maxFatigue[MAX_N];
    for (int X = 1; X <= N; X++) {
        maxFatigue[X-1] = 2 * S[indices[X-1]] + prefixSum[X-1];
    }
    
    for (int i = 0; i < N; i++) {
        printf("%lld\n", maxFatigue[i]);
    }
    
    return 0;
}