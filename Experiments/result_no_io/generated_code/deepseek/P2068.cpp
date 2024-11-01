#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000

long long sum[MAXN + 1];

int main() {
    int n, w;
    scanf("%d", &n);
    scanf("%d", &w);

    for (int i = 0; i < w; i++) {
        char op;
        int a, b;
        scanf(" %c %d %d", &op, &a, &b);

        if (op == 'x') {
            sum[a] += b;
        } else if (op == 'y') {
            long long result = 0;
            for (int j = a; j <= b; j++) {
                result += sum[j];
            }
            printf("%lld\n", result);
        }
    }

    return 0;
}