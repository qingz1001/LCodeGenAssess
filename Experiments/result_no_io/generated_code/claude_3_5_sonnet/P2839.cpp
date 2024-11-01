#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20000
#define MAX_Q 25000

int n, Q;
int s[MAX_N];
int sorted[MAX_N];
int tree[MAX_N * 4];

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = sorted[start];
        return;
    }
    int mid = (start + end) / 2;
    build(node * 2, start, mid);
    build(node * 2 + 1, mid + 1, end);
    tree[node] = (tree[node * 2] > tree[node * 2 + 1]) ? tree[node * 2] : tree[node * 2 + 1];
}

int query(int node, int start, int end, int l, int r, int k) {
    if (r < start || end < l) return -1;
    if (l <= start && end <= r) {
        if (end - start + 1 >= k) return tree[node];
        return -1;
    }
    int mid = (start + end) / 2;
    int left = query(node * 2, start, mid, l, r, k);
    int right = query(node * 2 + 1, mid + 1, end, l, r, k);
    return (left > right) ? left : right;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
        sorted[i] = s[i];
    }
    qsort(sorted, n, sizeof(int), compare);
    build(1, 0, n - 1);

    scanf("%d", &Q);
    int last_ans = 0;
    for (int i = 0; i < Q; i++) {
        int a, b, c, d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        int q[4] = {(a + last_ans) % n, (b + last_ans) % n, (c + last_ans) % n, (d + last_ans) % n};
        qsort(q, 4, sizeof(int), compare);
        a = q[0]; b = q[1]; c = q[2]; d = q[3];

        int left = 0, right = d - a + 1;
        while (left < right) {
            int mid = (left + right + 1) / 2;
            if (query(1, 0, n - 1, a, d, mid) != -1) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        last_ans = sorted[n - left];
        printf("%d\n", last_ans);
    }
    return 0;
}