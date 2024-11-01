#include <stdio.h>

// 函数声明
int canCut(int n, int k, int l, int* lengths);

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int lengths[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);
    }

    int low = 1, high = 0;
    for (int i = 0; i < n; i++) {
        if (lengths[i] > high) {
            high = lengths[i];
        }
    }

    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (canCut(n, k, mid, lengths)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }

    printf("%d\n", low);
    return 0;
}

// 判断是否能将原木切割成至少k段长度为l的小段
int canCut(int n, int k, int l, int* lengths) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += lengths[i] / l;
    }
    return count >= k;
}