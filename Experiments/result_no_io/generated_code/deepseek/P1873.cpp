#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000

int trees[MAXN];

long long woodCollected(int N, int H) {
    long long wood = 0;
    for (int i = 0; i < N; i++) {
        if (trees[i] > H) {
            wood += trees[i] - H;
        }
    }
    return wood;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int maxHeight = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &trees[i]);
        if (trees[i] > maxHeight) {
            maxHeight = trees[i];
        }
    }

    int low = 0, high = maxHeight;
    int result = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (woodCollected(N, mid) >= M) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", result);

    return 0;
}