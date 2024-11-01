#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

typedef long long ll;

typedef struct {
    int l, r, pos;
    ll sum;
} Segment;

int n, k, L, R;
ll a[MAXN], sum[MAXN];
Segment heap[MAXN];
int heap_size;

void swap(Segment *x, Segment *y) {
    Segment temp = *x;
    *x = *y;
    *y = temp;
}

void heap_push(Segment seg) {
    heap[++heap_size] = seg;
    int i = heap_size;
    while (i > 1 && heap[i].sum > heap[i / 2].sum) {
        swap(&heap[i], &heap[i / 2]);
        i /= 2;
    }
}

Segment heap_pop() {
    Segment ret = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while (i * 2 <= heap_size) {
        int j = i * 2;
        if (j + 1 <= heap_size && heap[j + 1].sum > heap[j].sum) j++;
        if (heap[i].sum >= heap[j].sum) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
    return ret;
}

int main() {
    scanf("%d %d %d %d", &n, &k, &L, &R);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }

    heap_size = 0;
    for (int i = 1; i <= n; i++) {
        if (i + L - 1 <= n) {
            int l = i + L - 1;
            int r = (i + R - 1 <= n) ? i + R - 1 : n;
            heap_push((Segment){l, r, i, sum[l] - sum[i - 1]});
        }
    }

    ll ans = 0;
    for (int i = 0; i < k; i++) {
        Segment seg = heap_pop();
        ans += seg.sum;
        if (seg.l < seg.r) {
            heap_push((Segment){seg.l + 1, seg.r, seg.pos, sum[seg.l + 1] - sum[seg.pos - 1]});
        }
    }

    printf("%lld\n", ans);
    return 0;
}