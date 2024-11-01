#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int sum; // 区间内1的总数
    int lazy; // 懒标记，0表示无操作，1表示全变0，2表示全变1，3表示取反
    int max_len; // 区间内连续1的最大长度
    int left_len; // 从左端点开始连续1的长度
    int right_len; // 从右端点开始连续1的长度
} Node;

Node tree[4 * MAXN];
int arr[MAXN];

void push_up(int node, int start, int end) {
    int mid = (start + end) / 2;
    int left_node = 2 * node, right_node = 2 * node + 1;

    tree[node].sum = tree[left_node].sum + tree[right_node].sum;
    tree[node].left_len = tree[left_node].left_len;
    tree[node].right_len = tree[right_node].right_len;
    tree[node].max_len = (tree[left_node].max_len > tree[right_node].max_len) ? tree[left_node].max_len : tree[right_node].max_len;

    if (tree[left_node].right_len + tree[right_node].left_len > tree[node].max_len) {
        tree[node].max_len = tree[left_node].right_len + tree[right_node].left_len;
    }

    if (tree[left_node].left_len == mid - start + 1) {
        tree[node].left_len += tree[right_node].left_len;
    }
    if (tree[right_node].right_len == end - mid) {
        tree[node].right_len += tree[left_node].right_len;
    }
}

void push_down(int node, int start, int end) {
    if (tree[node].lazy == 0) return;

    int mid = (start + end) / 2;
    int left_node = 2 * node, right_node = 2 * node + 1;

    if (tree[node].lazy == 1) {
        tree[left_node].sum = tree[right_node].sum = 0;
        tree[left_node].lazy = tree[right_node].lazy = 1;
        tree[left_node].left_len = tree[left_node].right_len = tree[left_node].max_len = 0;
        tree[right_node].left_len = tree[right_node].right_len = tree[right_node].max_len = 0;
    } else if (tree[node].lazy == 2) {
        tree[left_node].sum = mid - start + 1;
        tree[right_node].sum = end - mid;
        tree[left_node].lazy = tree[right_node].lazy = 2;
        tree[left_node].left_len = tree[left_node].right_len = tree[left_node].max_len = mid - start + 1;
        tree[right_node].left_len = tree[right_node].right_len = tree[right_node].max_len = end - mid;
    } else if (tree[node].lazy == 3) {
        tree[left_node].sum = (mid - start + 1) - tree[left_node].sum;
        tree[right_node].sum = (end - mid) - tree[right_node].sum;
        tree[left_node].lazy = 3 - tree[left_node].lazy;
        tree[right_node].lazy = 3 - tree[right_node].lazy;
        int temp;
        temp = tree[left_node].left_len;
        tree[left_node].left_len = tree[left_node].right_len;
        tree[left_node].right_len = temp;
        temp = tree[right_node].left_len;
        tree[right_node].left_len = tree[right_node].right_len;
        tree[right_node].right_len = temp;
    }

    tree[node].lazy = 0;
}

void build(int node, int start, int end) {
    if (start == end) {
        tree[node].sum = arr[start];
        tree[node].lazy = 0;
        tree[node].left_len = tree[node].right_len = tree[node].max_len = arr[start];
    } else {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
        push_up(node, start, end);
    }
}

void update(int node, int start, int end, int l, int r, int type) {
    if (l <= start && end <= r) {
        if (type == 0) {
            tree[node].sum = 0;
            tree[node].lazy = 1;
            tree[node].left_len = tree[node].right_len = tree[node].max_len = 0;
        } else if (type == 1) {
            tree[node].sum = end - start + 1;
            tree[node].lazy = 2;
            tree[node].left_len = tree[node].right_len = tree[node].max_len = end - start + 1;
        } else if (type == 2) {
            tree[node].sum = (end - start + 1) - tree[node].sum;
            tree[node].lazy = 3 - tree[node].lazy;
            int temp = tree[node].left_len;
            tree[node].left_len = tree[node].right_len;
            tree[node].right_len = temp;
        }
        return;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    if (l <= mid) update(2 * node, start, mid, l, r, type);
    if (r > mid) update(2 * node + 1, mid + 1, end, l, r, type);
    push_up(node, start, end);
}

int query_sum(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].sum;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    int sum = 0;
    if (l <= mid) sum += query_sum(2 * node, start, mid, l, r);
    if (r > mid) sum += query_sum(2 * node + 1, mid + 1, end, l, r);
    return sum;
}

int query_max_len(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node].max_len;
    }
    push_down(node, start, end);
    int mid = (start + end) / 2;
    int left_max = 0, right_max = 0;
    if (l <= mid) left_max = query_max_len(2 * node, start, mid, l, r);
    if (r > mid) right_max = query_max_len(2 * node + 1, mid + 1, end, l, r);
    int max_len = (left_max > right_max) ? left_max : right_max;
    if (l <= mid && r > mid) {
        int left_len = (l <= mid) ? tree[2 * node].right_len : 0;
        int right_len = (r > mid) ? tree[2 * node + 1].left_len : 0;
        if (left_len + right_len > max_len) {
            max_len = left_len + right_len;
        }
    }
    return max_len;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    build(1, 0, n - 1);
    while (m--) {
        int type, l, r;
        scanf("%d %d %d", &type, &l, &r);
        if (type == 0 || type == 1 || type == 2) {
            update(1, 0, n - 1, l, r, type);
        } else if (type == 3) {
            printf("%d\n", query_sum(1, 0, n - 1, l, r));
        } else if (type == 4) {
            printf("%d\n", query_max_len(1, 0, n - 1, l, r));
        }
    }
    return 0;
}