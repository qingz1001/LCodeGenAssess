#include <stdio.h>

#define MAXN 100001

int main() {
    int n, w;
    scanf("%d %d", &n, &w);

    long long arr[MAXN] = {0};
    for (int i = 0; i < w; ++i) {
        char op;
        int a, b;
        scanf(" %c %d %d", &op, &a, &b);
        if (op == 'x') {
            arr[a - 1] += b;
        } else if (op == 'y') {
            long long sum = 0;
            for (int j = a - 1; j <= b - 1; ++j) {
                sum += arr[j];
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}