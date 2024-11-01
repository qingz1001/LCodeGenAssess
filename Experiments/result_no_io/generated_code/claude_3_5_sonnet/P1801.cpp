#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200005

int a[MAX_N], u[MAX_N];
int tree[MAX_N];
int n, m;

int lowbit(int x) {
    return x & (-x);
}

void update(int x, int val) {
    while (x <= m) {
        tree[x] += val;
        x += lowbit(x);
    }
}

int query(int x) {
    int sum = 0;
    while (x > 0) {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}

int binary_search(int target) {
    int left = 1, right = m;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (query(mid) < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &u[i]);
    }
    
    int sorted[MAX_N];
    for (int i = 1; i <= m; i++) {
        sorted[i] = a[i];
    }
    qsort(sorted + 1, m, sizeof(int), cmp);
    
    int idx = 1;
    for (int i = 1; i <= m; i++) {
        if (i == u[idx]) {
            int pos = binary_search(idx);
            printf("%d\n", sorted[pos]);
            idx++;
        }
        int pos = (int)(lower_bound(sorted + 1, sorted + m + 1, a[i]) - sorted);
        update(pos, 1);
    }
    
    return 0;
}