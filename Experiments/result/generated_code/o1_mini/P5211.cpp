#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll min_val;
    int pos;
    ll lazy;
} Node;

int n, q;
ll arr_max = 1000000000;

Node tree[800000];
ll s[200005];

int build_pos(int l, int r, int idx) {
    if(l == r){
        tree[idx].min_val = s[l];
        tree[idx].pos = l;
        tree[idx].lazy = 0;
        return 0;
    }
    int mid = (l + r) / 2;
    build_pos(l, mid, idx*2);
    build_pos(mid+1, r, idx*2+1);
    if(tree[idx*2].min_val < tree[idx*2+1].min_val){
        tree[idx].min_val = tree[idx*2].min_val;
        tree[idx].pos = tree[idx*2].pos;
    }
    else if(tree[idx*2].min_val > tree[idx*2+1].min_val){
        tree[idx].min_val = tree[idx*2+1].min_val;
        tree[idx].pos = tree[idx*2+1].pos;
    }
    else{
        tree[idx].min_val = tree[idx*2].min_val;
        tree[idx].pos = tree[idx*2+1].pos;
    }
    tree[idx].lazy = 0;
    return 0;
}

void push_down(int l, int r, int idx){
    if(tree[idx].lazy != 0){
        int mid = (l + r) / 2;
        // Left child
        tree[idx*2].min_val += tree[idx].lazy;
        tree[idx*2+1].min_val += tree[idx].lazy;
        tree[idx*2].lazy += tree[idx].lazy;
        tree[idx*2+1].lazy += tree[idx].lazy;
        // Clear lazy
        tree[idx].lazy = 0;
    }
}

void update_range(int l, int r, int idx, int u, int v, ll val){
    if(v < l || u > r) return;
    if(u <= l && r <= v){
        tree[idx].min_val += val;
        tree[idx].lazy += val;
        return;
    }
    push_down(l, r, idx);
    int mid = (l + r) / 2;
    update_range(l, mid, idx*2, u, v, val);
    update_range(mid+1, r, idx*2+1, u, v, val);
    if(tree[idx*2].min_val < tree[idx*2+1].min_val){
        tree[idx].min_val = tree[idx*2].min_val;
        tree[idx].pos = tree[idx*2].pos;
    }
    else if(tree[idx*2].min_val > tree[idx*2+1].min_val){
        tree[idx].min_val = tree[idx*2+1].min_val;
        tree[idx].pos = tree[idx*2+1].pos;
    }
    else{
        tree[idx].min_val = tree[idx*2].min_val;
        tree[idx].pos = tree[idx*2+1].pos;
    }
}

ll query_min;
int query_pos;

void query_range(int l, int r, int idx, int u, int v){
    if(v < l || u > r) return;
    if(u <= l && r <= v){
        if(tree[idx].min_val < query_min){
            query_min = tree[idx].min_val;
            query_pos = tree[idx].pos;
        }
        else if(tree[idx].min_val == query_min){
            if(tree[idx].pos > query_pos){
                query_pos = tree[idx].pos;
            }
        }
        return;
    }
    push_down(l, r, idx);
    int mid = (l + r) / 2;
    query_range(l, mid, idx*2, u, v);
    query_range(mid+1, r, idx*2+1, u, v);
}

int main(){
    scanf("%d %d", &n, &q);
    for(int i=1;i<=n;i++) scanf("%lld", &s[i]);
    build_pos(1, n, 1);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d", &type);
        if(type == 1){
            int l, r;
            ll d;
            scanf("%d %d %lld", &l, &r, &d);
            update_range(1, n, 1, l, r, d);
        }
        else{
            int l, r;
            scanf("%d %d", &l, &r);
            query_min = 1e18;
            query_pos = l;
            query_range(1, n, 1, l, r);
            printf("%d\n", query_pos);
        }
    }
    return 0;
}