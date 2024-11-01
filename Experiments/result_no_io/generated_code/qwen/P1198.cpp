#include <stdio.h>
#include <stdlib.h>

#define MAXN 200010

int arr[MAXN];
int max_heap[MAXN * 4];
int t = 0, D;

void push(int x) {
    int p = ++max_heap[0];
    while (p / 2 && arr[x] > arr[max_heap[p / 2]]) {
        max_heap[p] = max_heap[p / 2];
        p /= 2;
    }
    max_heap[p] = x;
}

int pop() {
    int res = max_heap[1], l = 1, r = 2, p = 1;
    while (r <= max_heap[0]) {
        if (arr[l] < arr[r])
            p = r;
        else
            p = l;
        if (arr[res] >= arr[p])
            break;
        max_heap[l] = max_heap[p];
        l = p, r = p * 2;
    }
    max_heap[l] = max_heap[max_heap[0]];
    --max_heap[0];
    return res;
}

int query(int L) {
    int ans = 0;
    for (int i = 0; i < L; ++i) {
        if (arr[i] > ans)
            ans = arr[i];
    }
    return ans;
}

int main() {
    int M, D;
    scanf("%d %d", &M, &D);
    for (int i = 0; i < M; ++i) {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'Q') {
            int L;
            scanf("%d", &L);
            printf("%d\n", query(L));
        } else if (op[0] == 'A') {
            int n;
            scanf("%d", &n);
            n = (n + t) % D;
            arr[max_heap[0]] = n;
            push(max_heap[0]);
        }
    }
    return 0;
}