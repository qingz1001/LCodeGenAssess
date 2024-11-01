#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int value;
    int index;
} Node;

Node arr[MAXN];
int n, m, q;

int cmp_asc(const void *a, const void *b) {
    return ((Node*)a)->value - ((Node*)b)->value;
}

int cmp_desc(const void *a, const void *b) {
    return ((Node*)b)->value - ((Node*)a)->value;
}

int cmp_index(const void *a, const void *b) {
    return ((Node*)a)->index - ((Node*)b)->index;
}

void sort_range(int l, int r, int op) {
    if (op == 0) {
        qsort(arr + l - 1, r - l + 1, sizeof(Node), cmp_asc);
    } else {
        qsort(arr + l - 1, r - l + 1, sizeof(Node), cmp_desc);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i].value);
        arr[i].index = i + 1;
    }
    
    int op, l, r;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &op, &l, &r);
        sort_range(l, r, op);
    }
    
    qsort(arr, n, sizeof(Node), cmp_index);
    
    scanf("%d", &q);
    printf("%d\n", arr[q-1].value);
    
    return 0;
}