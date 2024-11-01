#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int p[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int merges = 0;
    while (n > 1) {
        int maxIndex = 0;
        for (int i = 1; i < n; i++) {
            if (p[i] > p[maxIndex]) {
                maxIndex = i;
            }
        }
        if (maxIndex == 0) {
            merges += n - 1;
            break;
        } else if (maxIndex == n - 1) {
            merges += n - 1;
            break;
        } else {
            merges++;
            for (int i = maxIndex; i < n - 1; i++) {
                p[i] += p[i + 1];
            }
            n--;
        }
    }

    printf("%d\n", merges);
    return 0;
}