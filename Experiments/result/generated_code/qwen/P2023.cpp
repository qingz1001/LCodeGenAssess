#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct {
    int type;
    int t;
    int g;
    int c;
} Operation;

int main() {
    int n, p;
    scanf("%d %d", &n, &p);
    long long *arr = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    int m;
    scanf("%d", &m);
    Operation *ops = (Operation *)malloc(m * sizeof(Operation));
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &ops[i].type, &ops[i].t, &ops[i].g);
        if (ops[i].type == 1 || ops[i].type == 2) {
            scanf("%d", &ops[i].c);
        }
    }

    for (int i = 0; i < m; i++) {
        if (ops[i].type == 1) {
            for (int j = ops[i].t - 1; j <= ops[i].g - 1; j++) {
                arr[j] = (arr[j] * ops[i].c) % p;
            }
        } else if (ops[i].type == 2) {
            for (int j = ops[i].t - 1; j <= ops[i].g - 1; j++) {
                arr[j] = (arr[j] + ops[i].c) % p;
            }
        } else if (ops[i].type == 3) {
            long long sum = 0;
            for (int j = ops[i].t - 1; j <= ops[i].g - 1; j++) {
                sum = (sum + arr[j]) % p;
            }
            printf("%lld\n", sum);
        }
    }

    free(arr);
    free(ops);
    return 0;
}