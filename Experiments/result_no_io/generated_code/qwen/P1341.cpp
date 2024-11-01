#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_LEN 26

typedef struct {
    char a;
    char b;
} Pair;

int compare(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    if (p1->a != p2->a) return p1->a - p2->a;
    return p1->b - p2->b;
}

void dfs(char *result, int pos, Pair pairs[], int n, int used[MAX_LEN], int count) {
    if (count == n) {
        printf("%s\n", result);
        exit(0);
    }
    for (int i = 0; i < n; i++) {
        if (used[pairs[i].a] && used[pairs[i].b]) continue;
        if (!used[pairs[i].a]) {
            result[pos++] = pairs[i].a;
            used[pairs[i].a] = 1;
        }
        if (!used[pairs[i].b]) {
            result[pos++] = pairs[i].b;
            used[pairs[i].b] = 1;
        }
        dfs(result, pos, pairs, n, used, count + 1);
        if (!used[pairs[i].a]) {
            used[pairs[i].a] = 0;
            pos--;
        }
        if (!used[pairs[i].b]) {
            used[pairs[i].b] = 0;
            pos--;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Pair pairs[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf(" %c %c", &pairs[i].a, &pairs[i].b);
    }

    qsort(pairs, n, sizeof(Pair), compare);

    char result[2 * n + 1];
    memset(result, '\0', sizeof(result));
    int used[MAX_LEN] = {0};

    dfs(result, 0, pairs, n, used, 0);

    printf("No Solution\n");
    return 0;
}