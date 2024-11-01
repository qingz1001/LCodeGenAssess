#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int l;
    int r;
    int id;
} Query;

int cmp(const void *a, const void *b){
    Query *qa = (Query *)a;
    Query *qb = (Query *)b;
    if(qa->r != qb->r)
        return qa->r - qb->r;
    return qa->l - qb->l;
}

#define MAXN 500005
#define MAXA 1000005

int BITree[MAXN];
int last_pos[MAXA];
Query queries_arr[MAXN];
int answers[MAXN];
int n, m;
int a[MAXN];

void update_BIT(int idx, int val){
    while(idx <= n){
        BITree[idx] += val;
        idx += idx & (-idx);
    }
}

int query_BIT(int idx){
    int res = 0;
    while(idx > 0){
        res += BITree[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int main(){
    // Fast IO
    // Read n
    scanf("%d", &n);
    for(int i=1;i<=n;i++) scanf("%d", &a[i]);
    // Read m
    scanf("%d", &m);
    for(int i=0;i<m;i++){
        scanf("%d %d", &queries_arr[i].l, &queries_arr[i].r);
        queries_arr[i].id = i;
    }
    // Sort queries by r
    qsort(queries_arr, m, sizeof(Query), cmp);
    // Initialize
    memset(last_pos, 0, sizeof(int)*(MAXA));
    int q_idx = 0;
    for(int i=1;i<=n;i++){
        if(last_pos[a[i]] != 0){
            update_BIT(last_pos[a[i]], -1);
        }
        update_BIT(i, 1);
        last_pos[a[i]] = i;
        while(q_idx < m && queries_arr[q_idx].r == i){
            int l = queries_arr[q_idx].l;
            int r = queries_arr[q_idx].r;
            answers[queries_arr[q_idx].id] = query_BIT(r) - query_BIT(l-1);
            q_idx++;
        }
    }
    // Print answers
    for(int i=0;i<m;i++) printf("%d\n", answers[i]);
    return 0;
}