#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct {
    long long a;
    long long b;
} Box;

void update(Box *boxes, int n, int l, int r, int a, int b) {
    for (int i = l; i <= r; i++) {
        boxes[i].a = (i - l + 1) % MOD;
        boxes[i].b = b;
    }
}

long long query(Box *boxes, int n, int l, int r) {
    long long sum = 0;
    for (int i = l; i <= r; i++) {
        sum += ((i - l + 1) * boxes[i].a) % MOD;
        if (sum >= MOD) sum -= MOD;
    }
    return sum;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    Box *boxes = (Box *)malloc(n * sizeof(Box));
    for (int i = 0; i < n; i++) {
        boxes[i].a = 1;
        boxes[i].b = 1;
    }

    while (q--) {
        int type, l, r;
        scanf("%d %d %d", &type, &l, &r);
        if (type == 1) {
            int a, b;
            scanf("%d %d", &a, &b);
            update(boxes, n, l - 1, r - 1, a, b);
        } else {
            printf("%lld\n", query(boxes, n, l - 1, r - 1));
        }
    }

    free(boxes);
    return 0;
}