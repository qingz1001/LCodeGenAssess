#include <stdio.h>
#include <stdlib.h>

#define MAXN 400005
#define INF (long long)(1e18)

typedef struct {
    int left, right;
    long long sum, maxSum, lazy;
} Node;

Node tree[MAXN << 2];

void pushDown(int node, int len) {
    if (tree[node].lazy != 0) {
        tree[node * 2].sum += (long long)tree[node].lazy * (len / 2);
        tree[node * 2 + 1].sum += (long long)tree[node].lazy * (len / 2);
        tree[node * 2].maxSum += (long long)tree[node].lazy * (len / 2);
        tree[node * 2 + 1].maxSum += (long long)tree[node].lazy * (len / 2);
        tree[node * 2].lazy += tree[node].lazy;
        tree[node * 2 + 1].lazy += tree[node].lazy;
        tree[node].lazy = 0;
    }
}

void buildTree(int node, int left, int right) {
    tree[node].left = left;
    tree[node].right = right;
    if (left == right) {
        scanf("%lld", &tree[node].sum);
        tree[node].maxSum = tree[node].sum;
        return;
    }
    int mid = (left + right) / 2;
    buildTree(node * 2, left, mid);
    buildTree(node * 2 + 1, mid + 1, right);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].maxSum = fmax(tree[node * 2].maxSum, tree[node * 2 + 1].maxSum);
    tree[node].maxSum = fmax(tree[node].maxSum, tree[node * 2].sum + tree[node * 2 + 1].maxSum);
}

void updateRange(int node, int left, int right, int add) {
    if (left <= tree[node].left && tree[node].right <= right) {
        tree[node].sum += (long long)add * (tree[node].right - tree[node].left + 1);
        tree[node].maxSum += (long long)add * (tree[node].right - tree[node].left + 1);
        tree[node].lazy += add;
        return;
    }
    pushDown(node, tree[node].right - tree[node].left + 1);
    int mid = (tree[node].left + tree[node].right) / 2;
    if (left <= mid)
        updateRange(node * 2, left, right, add);
    if (mid + 1 <= right)
        updateRange(node * 2 + 1, left, right, add);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].maxSum = fmax(tree[node * 2].maxSum, tree[node * 2 + 1].maxSum);
    tree[node].maxSum = fmax(tree[node].maxSum, tree[node * 2].sum + tree[node * 2 + 1].maxSum);
}

long long queryMaxSubarray(int node, int left, int right) {
    if (left <= tree[node].left && tree[node].right <= right) {
        return tree[node].maxSum;
    }
    pushDown(node, tree[node].right - tree[node].left + 1);
    long long ans = -INF;
    int mid = (tree[node].left + tree[node].right) / 2;
    if (left <= mid)
        ans = fmax(ans, queryMaxSubarray(node * 2, left, right));
    if (mid + 1 <= right)
        ans = fmax(ans, queryMaxSubarray(node * 2 + 1, left, right));
    return ans;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    buildTree(1, 1, n);
    while (q--) {
        int type, l, r, x;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d", &l, &r, &x);
            updateRange(1, l, r, x);
        } else if (type == 2) {
            scanf("%d %d", &l, &r);
            printf("%lld\n", queryMaxSubarray(1, l, r));
        }
    }
    return 0;
}