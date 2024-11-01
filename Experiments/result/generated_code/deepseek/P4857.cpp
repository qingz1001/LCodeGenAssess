#include <stdio.h>
#include <stdlib.h>

#define MAX_K 100000

typedef long long ll;

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    ll n;
    int k;
    scanf("%lld %d", &n, &k);

    int a[MAX_K];
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, k, sizeof(int), compare);

    ll commands[MAX_K];
    for (int i = 0; i < k; i++) {
        commands[i] = (n - 1) / a[i] + 1;
    }

    for (int i = 0; i < k; i++) {
        printf("%lld ", commands[i]);
    }
    printf("\n");

    return 0;
}