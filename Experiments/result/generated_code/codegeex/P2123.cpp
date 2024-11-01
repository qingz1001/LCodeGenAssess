#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left;
    int right;
} Minister;

int compare(const void *a, const void *b) {
    Minister *ministerA = (Minister *)a;
    Minister *ministerB = (Minister *)b;
    if (ministerA->left + ministerA->right > ministerB->left + ministerB->right) {
        return -1;
    } else if (ministerA->left + ministerA->right < ministerB->left + ministerB->right) {
        return 1;
    } else {
        if (ministerA->left > ministerB->left) {
            return -1;
        } else if (ministerA->left < ministerB->left) {
            return 1;
        } else {
            return 0;
        }
    }
}

long long calculateMaxMinBonus(int n, Minister ministers[]) {
    long long totalSum = 0;
    long long maxBonus = 0;
    long long currentBonus = 0;

    for (int i = 0; i < n; i++) {
        totalSum += ministers[i].left;
        currentBonus = ministers[i].right + (currentBonus > totalSum ? currentBonus : totalSum);
        if (currentBonus > maxBonus) {
            maxBonus = currentBonus;
        }
    }

    return maxBonus;
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        Minister ministers[n];
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &ministers[i].left, &ministers[i].right);
        }

        qsort(ministers, n, sizeof(Minister), compare);

        long long maxMinBonus = calculateMaxMinBonus(n, ministers);
        printf("%lld\n", maxMinBonus);
    }

    return 0;
}