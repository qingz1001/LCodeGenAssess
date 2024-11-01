#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int start, end, idx;
} Request;

int N, M;
int capacity[MAXN];
Request requests[MAXM];
int dp[MAXN];
int tree[MAXN * 4];

int cmp(const void *a, const void *b) {
    Request *ra = (Request *)a;
    Request *rb = (Request *)b;
    return ra->end - rb->end;
}

void update(int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (idx <= mid)
        update(node * 2, start, mid, idx, val);
    else
        update(node * 2 + 1, mid + 1, end, idx, val);
    tree[node] = (tree[node * 2] > tree[node * 2 + 1]) ? tree[node * 2] : tree[node * 2 + 1];
}

int query(int node, int start, int end, int l, int r) {
    if (l > end || r < start)
        return 0;
    if (l <= start && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int left = query(node * 2, start, mid, l, r);
    int right = query(node * 2 + 1, mid + 1, end, l, r);
    return (left > right) ? left : right;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &capacity[i]);
    
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &requests[i].start, &requests[i].end);
        requests[i].idx = i + 1;
    }
    
    qsort(requests, M, sizeof(Request), cmp);
    
    int ans = 0;
    for (int i = 0; i < M; i++) {
        int start = requests[i].start;
        int end = requests[i].end;
        int maxPrev = query(1, 1, N, 1, start - 1);
        
        if (maxPrev + 1 <= query(1, 1, N, start, end))
            continue;
        
        int canAllocate = 1;
        for (int j = start; j <= end; j++) {
            if (dp[j] + 1 > capacity[j]) {
                canAllocate = 0;
                break;
            }
        }
        
        if (canAllocate) {
            ans++;
            for (int j = start; j <= end; j++) {
                dp[j]++;
                update(1, 1, N, j, dp[j]);
            }
        }
    }
    
    printf("%d\n", ans);
    return 0;
}