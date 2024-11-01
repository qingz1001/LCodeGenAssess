#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

typedef long long ll;

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int N;
    int arr[MAXN], sorted[MAXN];
    ll cost = 0;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        sorted[i] = arr[i];
    }

    qsort(sorted, N, sizeof(int), cmp);

    for (int i = 0; i < N; i++) {
        if (arr[i] != sorted[i]) {
            for (int j = i + 1; j < N; j++) {
                if (arr[j] == sorted[i]) {
                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    cost += arr[i] + arr[j];
                    break;
                }
            }
        }
    }

    printf("%lld\n", cost);

    return 0;
}