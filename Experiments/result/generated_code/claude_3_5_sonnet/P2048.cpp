#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define INF 0x3f3f3f3f

typedef long long ll;

int n, k, L, R;
ll A[MAXN], sum[MAXN];
int q[MAXN], head, tail;
ll dp[MAXN];

struct Node {
    int pos;
    ll val;
} heap[MAXN];
int heap_size;

void swap(struct Node *a, struct Node *b) {
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(struct Node x) {
    int i = ++heap_size;
    heap[i] = x;
    while (i > 1 && heap[i].val > heap[i/2].val) {
        swap(&heap[i], &heap[i/2]);
        i /= 2;
    }
}

void pop() {
    heap[1] = heap[heap_size--];
    int i = 1, son;
    while (i*2 <= heap_size) {
        son = i*2;
        if (son < heap_size && heap[son+1].val > heap[son].val) son++;
        if (heap[i].val >= heap[son].val) break;
        swap(&heap[i], &heap[son]);
        i = son;
    }
}

int main() {
    scanf("%d%d%d%d", &n, &k, &L, &R);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &A[i]);
        sum[i] = sum[i-1] + A[i];
    }

    head = tail = 0;
    for (int i = L; i <= n; i++) {
        while (head < tail && sum[q[tail-1]] <= sum[i-L])
            tail--;
        q[tail++] = i-L;
        if (q[head] < i-R) head++;
        dp[i] = sum[i] - sum[q[head]];
        push((struct Node){i, dp[i]});
    }

    ll ans = 0;
    for (int i = 0; i < k; i++) {
        while (heap_size > 0 && heap[1].pos < L+i) pop();
        if (heap_size == 0) break;
        ans += heap[1].val;
        pop();
    }

    printf("%lld\n", ans);
    return 0;
}