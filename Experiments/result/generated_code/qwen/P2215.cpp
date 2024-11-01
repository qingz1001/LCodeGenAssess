#include <stdio.h>
#include <stdlib.h>

#define MAXN 10005
#define MAXM 1005

int n, m;
int arr[MAXN];
int queries[MAXM];

void preprocess() {
    for (int i = 1; i <= n; i++) {
        int pos = -1;
        for (int j = 1; j < i; j++) {
            if (arr[j] < arr[i]) {
                pos = j;
                break;
            }
        }
        if (pos == -1) {
            printf("Impossible\n");
        } else {
            for (int j = pos + 1; j <= i; j++) {
                printf("%d ", arr[j]);
            }
            printf("\n");
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &queries[i]);
    }

    preprocess();

    return 0;
}