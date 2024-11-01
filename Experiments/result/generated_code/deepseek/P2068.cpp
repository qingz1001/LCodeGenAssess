#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

int main() {
    int n, w;
    scanf("%d", &n);
    scanf("%d", &w);

    long long arr[MAXN + 1] = {0};

    for (int i = 0; i < w; i++) {
        char op;
        int a, b;
        scanf(" %c %d %d", &op, &a, &b);

        if (op == 'x') {
            arr[a] += b;
        } else if (op == 'y') {
            long long sum = 0;
            for (int j = a; j <= b; j++) {
                sum += arr[j];
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}