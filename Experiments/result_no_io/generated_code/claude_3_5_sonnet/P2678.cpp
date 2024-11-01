#include <stdio.h>

#define MAX_N 50001

int L, N, M;
int stones[MAX_N];

int check(int distance) {
    int count = 0, prev = 0;
    for (int i = 1; i <= N + 1; i++) {
        if (stones[i] - prev < distance) {
            count++;
        } else {
            prev = stones[i];
        }
    }
    return count <= M;
}

int binary_search() {
    int left = 1, right = L;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right;
}

int main() {
    scanf("%d %d %d", &L, &N, &M);
    
    for (int i = 1; i <= N; i++) {
        scanf("%d", &stones[i]);
    }
    stones[N + 1] = L;
    
    int result = binary_search();
    printf("%d\n", result);
    
    return 0;
}