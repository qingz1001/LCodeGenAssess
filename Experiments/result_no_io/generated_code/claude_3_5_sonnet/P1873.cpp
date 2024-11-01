#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

long long trees[MAX_N];
int N;
long long M;

long long cut_wood(long long height) {
    long long total = 0;
    for (int i = 0; i < N; i++) {
        if (trees[i] > height) {
            total += trees[i] - height;
        }
    }
    return total;
}

long long binary_search() {
    long long left = 0, right = 1000000000;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long wood = cut_wood(mid);
        if (wood >= M) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

int main() {
    scanf("%d %lld", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &trees[i]);
    }
    
    long long result = binary_search();
    printf("%lld\n", result);
    
    return 0;
}