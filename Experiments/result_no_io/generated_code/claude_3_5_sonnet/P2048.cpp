#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define INF 0x3f3f3f3f

typedef long long ll;

int n, k, L, R;
ll A[MAXN], sum[MAXN];
int q[MAXN], head, tail;
ll f[MAXN];

struct Node {
    int pos;
    ll val;
} heap[MAXN];
int heapSize;

void swap(struct Node *a, struct Node *b) {
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(int pos, ll val) {
    heapSize++;
    heap[heapSize].pos = pos;
    heap[heapSize].val = val;
    int now = heapSize;
    while (now > 1 && heap[now].val > heap[now/2].val) {
        swap(&heap[now], &heap[now/2]);
        now /= 2;
    }
}

void pop() {
    heap[1] = heap[heapSize--];
    int now = 1, next;
    while (now*2 <= heapSize) {
        next = now*2;
        if (next < heapSize && heap[next+1].val > heap[next].val) next++;
        if (heap[now].val >= heap[next].val) break;
        swap(&heap[now], &heap[next]);
        now = next;
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
        f[i] = sum[i] - sum[q[head]];
        push(i, f[i]);
    }

    ll ans = 0;
    for (int i = 0; i < k; i++) {
        while (heapSize && heap[1].pos < L+i) pop();
        ans += heap[1].val;
        pop();
    }

    printf("%lld\n", ans);
    return 0;
}