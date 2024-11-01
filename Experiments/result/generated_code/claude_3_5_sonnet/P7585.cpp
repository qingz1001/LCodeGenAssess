#include <stdio.h>
#include <stdlib.h>

#define MAX_M 300000

long long marbles[MAX_M];
int N, M;

int check(long long mid) {
    long long count = 0;
    for (int i = 0; i < M; i++) {
        count += marbles[i] / mid;
    }
    return count >= N;
}

long long binary_search() {
    long long left = 1, right = 1e9, mid, ans = 0;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%lld", &marbles[i]);
    }
    
    printf("%lld\n", binary_search());
    
    return 0;
}