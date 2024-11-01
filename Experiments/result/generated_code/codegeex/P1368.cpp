#include <stdio.h>

#define MAXN 300001

int a[MAXN], b[MAXN], c[MAXN], n;

void minrep() {
    int i, j, k;
    for (i = 0, j = 1, k = 0; i < n && j < n && k < n;) {
        if (b[i] == b[j]) {
            i++;
            j++;
            k++;
        } else if (b[i] < b[j]) {
            j = j + k + 1;
            if (j > n) j -= n;
            k = 0;
        } else {
            i = i + k + 1;
            if (i > n) i -= n;
            k = 0;
        }
    }
    if (i > j) {
        j = i;
    }
    for (i = 0; i < n; i++) {
        c[i] = b[(j + i) % n];
    }
}

int main() {
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    minrep();
    for (i = 0; i < n; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");
    return 0;
}