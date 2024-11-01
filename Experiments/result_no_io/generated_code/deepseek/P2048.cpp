#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

typedef long long ll;

int n, k, L, R;
ll A[MAXN], sum[MAXN];

typedef struct {
    ll val;
    int l, r, pos;
} Node;

Node heap[MAXN];
int heap_size;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(Node x) {
    heap[++heap_size] = x;
    int i = heap_size;
    while (i > 1 && heap[i].val > heap[i / 2].val) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

Node heap_pop() {
    Node ret = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while (i * 2 <= heap_size) {
        int j = i * 2;
        if (j + 1 <= heap_size && heap[j + 1].val > heap[j].val) j++;
        if (heap[i].val >= heap[j].val) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
    return ret;
}

int main() {
    scanf("%d %d %d %d", &n, &k, &L, &R);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &A[i]);
        sum[i] = sum[i - 1] + A[i];
    }

    for (int i = 1; i <= n; i++) {
        if (i + L - 1 <= n) {
            int l = i + L - 1;
            int r = (i + R - 1 <= n) ? i + R - 1 : n;
            heap_push((Node){sum[l] - sum[i - 1], l, r, i});
        }
    }

    ll ans = 0;
    for (int i = 0; i < k; i++) {
        Node top = heap_pop();
        ans += top.val;
        if (top.l < top.r) {
            heap_push((Node){sum[top.l + 1] - sum[top.pos - 1], top.l + 1, top.r, top.pos});
        }
    }

    printf("%lld\n", ans);
    return 0;
}