#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef struct {
    int a;
    int h;
    int c;
} Node;

Node nodes[MAXN];
int n;

int compare(const void *a, const void *b) {
    return ((Node *)b)->h - ((Node *)a)->h;
}

long long min_cost() {
    qsort(nodes, n, sizeof(Node), compare);
    long long cost = 0;
    for (int i = 0; i < n; i++) {
        if (nodes[i].h > nodes[i].a) {
            cost += (nodes[i].h - nodes[i].a) * nodes[i].c;
        }
    }
    return cost;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &nodes[i].a, &nodes[i].h, &nodes[i].c);
    }
    printf("%lld\n", min_cost());
    return 0;
}