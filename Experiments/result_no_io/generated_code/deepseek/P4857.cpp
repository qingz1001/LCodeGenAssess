#include <stdio.h>
#include <stdlib.h>

#define MAX_K 100000

int main() {
    long long n;
    int k;
    scanf("%lld %d", &n, &k);

    int a[MAX_K];
    for (int i = 0; i < k; i++) {
        scanf("%d", &a[i]);
    }

    long long steps[MAX_K] = {0};
    long long current_step = 0;

    while (current_step < n) {
        for (int i = 0; i < k && current_step < n; i++) {
            steps[i]++;
            current_step += a[i];
        }
    }

    for (int i = 0; i < k; i++) {
        printf("%lld ", steps[i]);
    }
    printf("\n");

    return 0;
}