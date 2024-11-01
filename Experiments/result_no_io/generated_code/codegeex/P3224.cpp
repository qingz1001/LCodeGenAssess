#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int parent[MAXN];
int rank[MAXN];

void makeSet(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findSet(int x) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int arr[MAXN];
int sorted_arr[MAXN];

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            sorted_arr[k++] = arr[i++];
        } else {
            sorted_arr[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        sorted_arr[k++] = arr[i++];
    }
    while (j <= right) {
        sorted_arr[k++] = arr[j++];
    }
    for (int l = left; l <= right; l++) {
        arr[l] = sorted_arr[l];
    }
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    makeSet(n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }

    mergeSort(1, n);

    for (int i = 1; i <= n; i++) {
        sorted_arr[arr[i]] = i;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unionSet(u, v);
    }

    int q;
    scanf("%d", &q);

    while (q--) {
        char op;
        int x, y;
        scanf(" %c %d %d", &op, &x, &y);
        if (op == 'B') {
            unionSet(x, y);
        } else if (op == 'Q') {
            int rootX = findSet(x);
            int k = sorted_arr[y];
            if (k > n) {
                printf("-1\n");
            } else {
                printf("%d\n", arr[k]);
            }
        }
    }

    return 0;
}