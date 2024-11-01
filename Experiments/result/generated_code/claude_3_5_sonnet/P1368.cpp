#include <stdio.h>
#include <string.h>

#define MAXN 300005

int n;
int a[MAXN * 2];

int min_representation() {
    int i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n) {
        if (a[i + k] == a[j + k]) {
            k++;
        } else if (a[i + k] > a[j + k]) {
            i = i + k + 1;
            if (i <= j) i = j + 1;
            k = 0;
        } else {
            j = j + k + 1;
            if (j <= i) j = i + 1;
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