#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MOD 1000000007

typedef struct {
    int x;
    int y;
} Pair;

int compare(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    if (p1->x == p2->x) {
        return p1->y - p2->y;
    }
    return p1->x - p2->x;
}

bool canSit(int n, int p, int a, int b) {
    if (p == 0) {
        return a != b;
    }
    if (p == 1) {
        return (a + 1) % n != b && (a - 1 + n) % n != b;
    }
    if (p == 2) {
        return (a + 2) % n != b && (a - 2 + n) % n != b && (a + 1) % n != b && (a - 1 + n) % n != b;
    }
    return true;
}

int main() {
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);

    Pair *dislikes = (Pair *)malloc(k * sizeof(Pair));
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &dislikes[i].x, &dislikes[i].y);
    }

    qsort(dislikes, k, sizeof(Pair), compare);

    long long ans = 1;
    int last = 0;
    for (int i = 0; i < k; i++) {
        if (dislikes[i].x == n) {
            if (!canSit(n, p, dislikes[i].x, dislikes[i].y)) {
                printf("0\n");
                return 0;
            }
            last = i;
        }
    }

    for (int i = last + 1; i < k; i++) {
        if (dislikes[i].x == dislikes[i - 1].x) {
            if (!canSit(n, p, dislikes[i].x, dislikes[i].y)) {
                printf("0\n");
                return 0;
            }
        } else {
            ans = (ans * (n - 1)) % MOD;
        }
    }

    ans = (ans * (n - 1)) % MOD;
    printf("%lld\n", ans);

    free(dislikes);
    return 0;
}