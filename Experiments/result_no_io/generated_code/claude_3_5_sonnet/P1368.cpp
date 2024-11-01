#include <stdio.h>

#define MAXN 300005

int n;
int a[MAXN * 2];

int min_representation() {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        int t = a[i + k] - a[j + k];
        if (t == 0) {
            k++;
        } else {
            if (t > 0) {
                i += k + 1;
            } else {
                j += k + 1;
            }
            if (i == j) j++;
            k = 0;
        }
    }
    return i < j ? i : j;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }

    int start = min_representation();
    for (int i = 0; i < n; i++) {
        printf("%d ", a[start + i]);
    }
    printf("\n");

    return 0;
}