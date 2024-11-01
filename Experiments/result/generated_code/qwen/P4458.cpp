#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct {
    int *data;
    int size;
} Array;

Array* create_array(int size) {
    Array *arr = (Array*)malloc(sizeof(Array));
    arr->data = (int*)calloc(size, sizeof(int));
    arr->size = size;
    return arr;
}

void free_array(Array *arr) {
    free(arr->data);
    free(arr);
}

void update_range(Array *arr, int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        arr->data[i] += value;
    }
}

long long query_sum(Array *arr, int left, int right) {
    long long sum = 0;
    for (int i = left; i <= right; i++) {
        sum = (sum + arr->data[i]) % MOD;
    }
    return sum;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Array *tree = create_array(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &tree->data[i]);
    }

    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int u, v, d;
            scanf("%d %d %d", &u, &v, &d);
            u--; v--;
            if (u > v) {
                int temp = u;
                u = v;
                v = temp;
            }
            update_range(tree, u, v, d);
        } else if (op == 2) {
            int l, r;
            scanf("%d %d", &l, &r);
            l--; r--;
            printf("%lld\n", query_sum(tree, l, r));
        }
    }

    free_array(tree);
    return 0;
}